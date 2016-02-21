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
                state = autoAdvance ? ShooterState::FIRE : ShooterState::NONE;
            }
            break;
        case ShooterState::SPINNING:
            // Start spinning up the fly wheels.
            spinSpeed = 0.62; // TODO: Calculate speed!
            talonMaster->Set(spinSpeed);

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

bool Shooter::IsActivated()
{
    return state != ShooterState::NONE;
}
