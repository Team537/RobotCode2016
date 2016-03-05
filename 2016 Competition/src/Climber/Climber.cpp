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

#if NEW_JOYSTICK
            if (joystickSecondary->GetRawAxis(JOYSTICK_AXIS_TRIGGER_LEFT) > CONTROLLER_DEADBAND)
#else
            if (retractButton->WasDown())
#endif
            {
                state = ClimberState::RETRACT;
            }

#if NEW_JOYSTICK
            if (joystickSecondary->GetRawAxis(JOYSTICK_AXIS_TRIGGER_RIGHT) > CONTROLLER_DEADBAND)
#else
            if (deployHalfButton->WasDown())
#endif
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
            ToggleExtend(false);
            ToggleStage2(false);
            ToggleStage1(true);
            break;
        case EXTEND_HALF:
            ToggleStage1(false); //false = extended for stage 1
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
    SmartDashboard::PutBoolean("Climber Stage 1", deployStage1->Get());
    SmartDashboard::PutBoolean("Climber Stage 2", deployStage2->Get());
    SmartDashboard::PutBoolean("Climber Stage Extend", extendStage3->Get());
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
