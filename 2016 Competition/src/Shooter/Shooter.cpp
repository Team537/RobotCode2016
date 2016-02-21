#include <Shooter/Shooter.hpp>

void Shooter::Update(bool teleop)
{
    if (teleop)
    {
        if (autoShootButton->WasDown())
        {
            autoAdvance = true;
            state = ShooterState::AIMING;
        }

        if (manualAimButton->WasDown())
        {
            autoAdvance = false;
            state = ShooterState::AIMING;
        }

        if (manualFireButton->WasDown())
        {
            autoAdvance = false;
            state = ShooterState::SPINNING;
        }
    }

    switch (state)
    {
        case ShooterState::AIMING:
            // Tells the drive train to target a goal.
            drive->SetState(DriveTrain::DriveState::TELEOP_SHOOT);

            // Once targeted advance / pause.
            if (drive->IsWaiting() || drive->IsTeleopControl() || gotoNoneButton->WasDown())
            {
<<<<<<< HEAD
                state = autoAdvance ? ShooterState::SPINNING : ShooterState::NONE;
=======
                state = autoAdvance ? ShooterState::FIRE : ShooterState::NONE;
>>>>>>> cdc456a5b622ec8b365d3a6cafb3321718227ea9
            }
            break;
        case ShooterState::SPINNING:
            // Start spinning up the fly wheels.
<<<<<<< HEAD
            {
                double sqrtTop = G * pow((vision->GetGoalDistance() * 0.0254), 2);
                double sqrtBottom = 2 * ((GOAL_GROUND_HEIGHT * 0.0254) - (tan(SHOOTER_ANGLE) * (vision->GetGoalDistance() * 0.0254)));
                spinSpeed = sqrt(sqrtTop / sqrtBottom) / cos(SHOOTER_ANGLE);
            }

            talonMaster->Set(spinSpeed * MS_TO_SPEED);
=======
            spinSpeed = 0.62; // TODO: Calculate speed!
            talonMaster->Set(spinSpeed);
>>>>>>> cdc456a5b622ec8b365d3a6cafb3321718227ea9

            // Waits until ramped up!
            if ((fabs(talonMaster->GetSpeed()) < fabs(spinSpeed) + SHOOTER_SPEED_DEADBAND && fabs(talonMaster->GetSpeed()) > fabs(spinSpeed) - SHOOTER_SPEED_DEADBAND) || gotoNoneButton->WasDown())
            {
                state = ShooterState::FIRE;
                extendTimer->Reset();
            }
            break;
        case ShooterState::FIRE:
            // Extends if the timer has not went off.
            if (extendTimer->Get() == 0.0f)
            {
                extendSolenoid->Set(true);
                extendTimer->Reset();
                extendTimer->Start();
            }

            // Wait one second before continuing.
            if (extendTimer->Get() > 1.0f || gotoNoneButton->WasDown())
            {
                extendTimer->Stop();
                extendTimer->Reset();
                state = ShooterState::NONE;
            }
            break;
        case ShooterState::NONE:
            // Returns to states before.
            talonMaster->Set(0);
            extendSolenoid->Set(false);
            break;
    }
}

void Shooter::Dashboard()
{
    SmartDashboard::PutBoolean("Shooter Activated", IsActivated());
    SmartDashboard::PutBoolean("Shooter Speed", spinSpeed);
}

void Shooter::SetState(ShooterState shooterState)
{
    state = shooterState;
}

void Shooter::AutoShoot()
{
    autoAdvance = true;
    SetState(ShooterState::AIMING);
}

bool Shooter::IsActivated()
{
    return state != ShooterState::NONE;
}
