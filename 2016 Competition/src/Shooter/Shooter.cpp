#include <Shooter/Shooter.hpp>

void Shooter::Update(bool teleop)
{
    if (teleop)
    {
		// talonMaster->Set(joystickSecondary->GetRawAxis(JOYSTICK_AXIS_LEFT_Y));
        // extendSolenoid->Set(joystickSecondary->GetRawButton(JOYSTICK_B));
		
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
                state = autoAdvance ? ShooterState::AIMING : ShooterState::NONE;
            }
            break;
        case ShooterState::SPINNING:
            // Start spinning up the fly wheels.
        {
            double sqrtTop = G * pow((vision->GetGoalDistance() * 0.0254), 2);
            double sqrtBottom = 2 * ((GOAL_GROUND_HEIGHT * 0.0254) - (tan(SHOOTER_ANGLE) * (vision->GetGoalDistance() * 0.0254)));
            spinSpeed = sqrt(sqrtTop / sqrtBottom) / cos(SHOOTER_ANGLE);
        }

            talonMaster->Set(spinSpeed * MS_TO_SPEED);

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

            // Wait half second before continuing.
            if (extendTimer->Get() > 0.5f || gotoNoneButton->WasDown())
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
