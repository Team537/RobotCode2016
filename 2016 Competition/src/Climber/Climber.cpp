#include <Climber/Climber.hpp>

void Climber::Update(bool teleop)
{
    if (teleop)
    {
        // This will cause other robot functions to slow down / stop!
        if (toggleClimbMode->WasDown())
        {
            state = ClimberState::NONE;
            climbing = !climbing;
        }

        // If climbing update controls.
        if (climbing)
        {
            if (gotoNoneButton->WasDown())
            {
                state = ClimberState::NONE;
            }

            if (retractButton->WasDown())
            {
                state = ClimberState::RETRACT;
            }

            if (deployHalfButton->WasDown())
            {
                state = ClimberState::EXTEND_HALF;
            }

            if (deployFullButton->WasDown())
            {
                state = ClimberState::EXTEND_FULL;
            }

            if (deployHooksButton->WasDown())
            {
                state = ClimberState::EXTEND_HOOKS;
            }

            if (pullUpButton->WasDown())
            {
                state = ClimberState::PULL_UP;
            }
        }
        else
        {
            state = ClimberState::RETRACT;
        }
    }

    switch (state)
    {
        case NONE:
            break;
        case RETRACT:
            ToggleStage1(true);
            ToggleStage2(false);
            ToggleExtend(false);
            break;
        case EXTEND_HALF:
            ToggleStage1(false); // false = extended for stage 1
            ToggleStage2(false);
            ToggleExtend(false);
            break;
        case EXTEND_FULL:
            ToggleStage1(false);
            ToggleStage2(true);
            break;
        case EXTEND_HOOKS:
            ToggleExtend(true);
            break;
        case PULL_UP:
            ToggleExtend(false);
            break;
    }
}

void Climber::Dashboard()
{
    SmartDashboard::PutString("Climber State", stateNames[state]);
    SmartDashboard::PutBoolean("Is Climbing", climbing);
    SmartDashboard::PutBoolean("Climber Stage 1", !deployStage1->Get());
    SmartDashboard::PutBoolean("Climber Stage 2", deployStage2->Get());
    SmartDashboard::PutBoolean("Climber Stage Extend", extendStage3->Get());
    SmartDashboard::PutBoolean("Deploy Right One Read Switch", deployStage1Right->Get());
    SmartDashboard::PutBoolean("Deploy Left One Read Switch", deployStage1Left->Get());
    SmartDashboard::PutBoolean("Deploy Right Two Read Switch", deployStage2Right->Get());
    SmartDashboard::PutBoolean("Deploy Left Two Read Switch", deployStage2Left->Get());
}

void Climber::ToggleStage1(bool extend)
{
    deployStage1->Set(extend);
}

void Climber::ToggleStage2(bool extend)
{
    deployStage2->Set(extend);
}

void Climber::ToggleExtend(bool extend)
{
    extendStage3->Set(extend);
}

bool Climber::IsClimbing()
{
    return climbing;
}

void Climber::Init()
{
    climbing = false;
    state = RETRACT;
}
