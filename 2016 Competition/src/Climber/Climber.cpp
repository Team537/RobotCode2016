#include <Climber/Climber.hpp>

void Climber::Init()
{
    climbing = false;
    state = RETRACT;
}

void Climber::Update(const bool& teleop)
{
    if (teleop)
    {
        // This will cause other robot functions to slow down / stop!
        if (toggleClimbMode->WasDown())
        {
            lastState = climbing ? state : lastState;
            state = climbing ? state : lastState;
            climbing = !climbing;
        }

        if (noModeHalf->WasDown()) { // !climbing &&
            printf("%s", "No Mode Half Toggled!");
            state = (state != ClimberState::EXTEND_HALF) ? ClimberState::EXTEND_HALF : ClimberState::RETRACT;
        }

        // If climbing update controls.
        if (climbing)
        {
            if (toggleFullSpeed->WasDown())
            {
                fullSpeed = !fullSpeed;
            }

            if (gotoNoneButton->WasDown())
            {
                SetState(ClimberState::NONE);
            }

            if (retractButton->WasDown())
            {
                if (state == EXTEND_HOOKS) {
                    SetState(ClimberState::EXTEND_FULL);
                } else if (state == EXTEND_FULL) {
                    SetState(ClimberState::EXTEND_HALF);
                } else if (state == EXTEND_HALF) {
                    if (hookState == RETRACTED) {
                        SetState(ClimberState::RETRACT);
                    }
                }
            }

            if (NEW_JOYSTICK ? deployHalfButton->GetAxis() > JOYSTICK_DEADBAND : deployHalfButton->GetKey())
            {
                SetState(ClimberState::EXTEND_HALF);
            }

            if (NEW_JOYSTICK ? deployFullButton->GetAxis() > JOYSTICK_DEADBAND : deployFullButton->GetKey())
            {
                SetState(ClimberState::EXTEND_FULL);
            }

            if (deployHooksButton->WasDown())
            {
                if (state != RETRACTED) {
                    DeployHooks(HookState::EXTENDED);
                }
            }

            if (pullUpButton->WasDown())
            {
                DeployHooks(HookState::RETRACTED);
            }
        }
   //     else
   //     {
   //         SetState(ClimberState::RETRACT);
   //     }
    }

    if (!collector->IsCollecting())
    {
        state = EXTEND_HALF;
    }

    switch (state)
    {
        case NONE:
            timer->Stop();
            timer->Reset();
            break;
        case RETRACT:
            ToggleStage1(false);
            ToggleStage2(false);
            hookState = RETRACTED;
            TogglePopup(false);
            timer->Stop();
            timer->Reset();
            break;
        case EXTEND_HALF:
            ToggleStage1(true);
            ToggleStage2(false);
            //updatePoupup
            timer->Start();
            if (timer->Get() > 2) {
               TogglePopup(true);
            } else if (timer->Get() > 3) {
               TogglePopup(false);
               timer->Stop();
               timer->Reset();
            }
            break;
        case EXTEND_FULL:
            ToggleStage1(true);
            ToggleStage2(true);
            UpdatePopUp();
            break;
        default:
            break;
    }

    switch (hookState)
    {
        case EXTENDED:
            ToggleExtend(true);
            break;
        case RETRACTED:
            ToggleExtend(false);
            break;
        default:
            break;
    }
}

void Climber::SetState(ClimberState state)
{
    if (this->state != state) {
       /* if (this->state == NONE || this->state == RETRACT) {
            timer->Stop();
            timer->Reset();
            timer->Start();
        }*/

        this->state = state;
    }
}

void Climber::DeployHooks(HookState hookState)
{
    if (this->hookState != hookState)
    {
        this->hookState = hookState;
    }
}

void Climber::UpdatePopUp()
{
    if (timer->Get() > 1) {
        TogglePopup(true);
    } else if (timer->Get() > 2) {
        TogglePopup(false);
        timer->Stop();
        timer->Reset();
    }
}

void Climber::Dashboard()
{
    SmartDashboard::PutString("Climber State", stateNames[state]);
    SmartDashboard::PutString("Climber Hook State", stateNames[hookState]);
    SmartDashboard::PutBoolean("Is Climbing", climbing);
    SmartDashboard::PutBoolean("Climber Stage 1", !deployStage1->Get());
    SmartDashboard::PutBoolean("Climber Stage 2", deployStage2->Get());
    SmartDashboard::PutBoolean("Climber Stage Extend", hooksStage3->Get());
    SmartDashboard::PutBoolean("Climber Stage Pop Up", popUp->Get());
    SmartDashboard::PutBoolean("Deploy Right One Read Switch", deployStage1Right->Get());
    SmartDashboard::PutBoolean("Deploy Left One Read Switch", deployStage1Left->Get());
    SmartDashboard::PutBoolean("Deploy Right Two Read Switch", deployStage2Right->Get());
    SmartDashboard::PutBoolean("Deploy Left Two Read Switch", deployStage2Left->Get());
}

void Climber::ToggleStage1(const bool& extend)
{
    deployStage1->Set(!extend);
}

void Climber::ToggleStage2(const bool& extend)
{
    deployStage2->Set(extend);
}

void Climber::ToggleExtend(const bool& extend)
{
    hooksStage3->Set(extend);
}

void Climber::TogglePopup(const bool& up)
{
    popUp->Set(up);
}
