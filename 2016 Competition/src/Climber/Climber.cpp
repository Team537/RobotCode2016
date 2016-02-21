#include <Climber/Climber.hpp>

void Climber::Update(bool teleop)
{
    if (teleop)
    {
        // This will cause other robot functions to slow down / stop!
        if (toggleClimbMode->WasDown())
        {
            climbing = !climbing;
        }

        // If climbing update controls.
        if (climbing)
        {
            if (retractButton->WasDown())
            {
                targetState = ClimberState::RETRACT;
            }

            if (deployHalfButton->WasDown())
            {
                targetState = ClimberState::EXTEND_HALF;
            }

            if (deployFullButton->WasDown())
            {
                targetState = ClimberState::EXTEND_FULL;
            }

            if (pullUpButton->WasDown())
            {
                targetState = ClimberState::PULL_UP;
            }
        }
        else
        {
            targetState = ClimberState::RETRACT;
        }
    }

    switch (state)
    {
        case NONE:
            break;
        case RETRACT:
            // If any are extended start the retract!
            if ((deployStage1->Get() || deployStage2->Get() || extendStage3->Get()) && timer->Get() == 0.0f)
            {
                timer->Reset();
                timer->Start();
            }
            else
            {
                timer->Stop();
                timer->Reset();
                // Case switch out point!
                targetState = targetState == ClimberState::RETRACT ? ClimberState::NONE : targetState;
                state = targetState;
            }

            // Retract the extended stage 3 and/or stage 2.
            if (extendStage3->Get() || deployStage2->Get())
            {
                ToggleExtend(false);
                ToggleStage2(false);
            }

            // Retract stage 1 after 1.5 seconds.
            if (deployStage1->Get() && timer->Get() > 1.5f)
            {
                ToggleStage1(false);
            }
            break;
        case EXTEND_HALF:
            // Extends stage 1 and retract all others.
            if (!deployStage1->Get() && deployStage2->Get() && extendStage3->Get())
            {
                timer->Reset();
                timer->Start();
            }
            else
            {
                timer->Stop();
                timer->Reset();
                // Case switch out point!
                targetState = targetState == ClimberState::EXTEND_HALF ? ClimberState::NONE : targetState;
                state = targetState;
            }

            // Extend stage 1 if not already extended!
            if (!deployStage1->Get())
            {
                ToggleStage1(true);
            }

            // Retract all stages but stage 1.
            if (deployStage2->Get() || extendStage3->Get())
            {
                ToggleStage2(false);
                ToggleExtend(false);
            }
            break;
        case EXTEND_FULL:
<<<<<<< HEAD
            // Extend all stages if they are not already extended!
=======
            // Extend all stages if they are not alredy extended!
>>>>>>> cdc456a5b622ec8b365d3a6cafb3321718227ea9
            if ((!deployStage1->Get() || !deployStage2->Get() || !extendStage3->Get()) && timer->Get() == 0.0f)
            {
                timer->Reset();
                timer->Start();
            }
            else
            {
                timer->Stop();
                timer->Reset();
                // Case switch out point!
                targetState = targetState == ClimberState::EXTEND_FULL ? ClimberState::NONE : targetState;
                state = targetState;
            }

            // Extend stage 1.
            if (!deployStage1->Get())
            {
                ToggleStage1(true);
            }

            // Extend stage 2 and extend 3 after 1.25 seconds.
            if (!deployStage2->Get() && timer->Get() > 1.25f)
            {
                ToggleStage2(true);
                ToggleExtend(true);
            }
            break;
        case PULL_UP:
            // Keep the hooks out, but pull back the other solenoids.
            ToggleStage1(false);
            ToggleStage2(false);
            ToggleExtend(true);
            break;
    }
}

void Climber::Dashboard()
{
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
