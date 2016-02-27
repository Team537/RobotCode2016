#include <Shooter/Shooter.hpp>

void Shooter::Update(bool teleop)
{
    if (teleop)
    {
        if (gotoNoneButton0->WasDown() || gotoNoneButton1->WasDown())
        {
            drive->SetState(DriveTrain::DriveState::NONE);
            state = ShooterState::NONE;
        }

#if NEW_JOYSTICK
        if (joystickPrimary->GetRawAxis(JOYSTICK_AXIS_TRIGGER_LEFT) > CONTROLLER_DEADBAND)
#else
        if (autoShootButton->WasDown())
#endif
        {
            autoAdvance = true;
            state = ShooterState::AIMING;
        }

#if NEW_JOYSTICK
        if (joystickSecondary->GetRawAxis(JOYSTICK_AXIS_TRIGGER_LEFT) > CONTROLLER_DEADBAND)
#else
        if (manualAimButton->WasDown())
#endif
        {
            autoAdvance = false;
            state = ShooterState::AIMING;
        }

#if NEW_JOYSTICK
        if (joystickSecondary->GetRawAxis(JOYSTICK_AXIS_TRIGGER_RIGHT) > CONTROLLER_DEADBAND)
#else
        if (manualFireButton->WasDown())
#endif
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
            if (drive->IsWaiting() || drive->IsTeleopControl())
            {
                state = autoAdvance ? ShooterState::AIMING : ShooterState::NONE;
            }
            break;
        case ShooterState::SPINNING:
            // Start spinning up the fly wheels.
        {
            // double sqrtTop = G * pow((vision->GetGoalDistance() * 0.0254), 2);
            // double sqrtBottom = 2 * ((GOAL_GROUND_HEIGHT * 0.0254) - (tan(SHOOTER_ANGLE) * (vision->GetGoalDistance() * 0.0254)));
            // spinSpeed = sqrt(sqrtTop / sqrtBottom) / cos(SHOOTER_ANGLE);
            // spinSpeed *= SHOOTER_MS_TO_ENCODER;
            spinSpeed = 1.0f;
        }

        drive->SetState(DriveTrain::DriveState::NONE);

            talonMaster->Set(spinSpeed);

            // Waits until ramped up!
            if ((fabs(talonMaster->GetEncVel()) < fabs(spinSpeed) + SHOOTER_SPEED_TOLERANCE && fabs(talonMaster->GetSpeed()) > fabs(spinSpeed) - SHOOTER_SPEED_TOLERANCE))
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
            if (extendTimer->Get() > 0.5f)
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
    SmartDashboard::PutString("Shooter State", state == AIMING ? "Aiming" : state == SPINNING ? "Spinning" : state == FIRE ? "Firing" : "None");
    SmartDashboard::PutBoolean("Shooter Activated", IsActivated());
    SmartDashboard::PutBoolean("Shooter Speed", spinSpeed);
    SmartDashboard::PutBoolean("Shooter Encoder", spinSpeed);
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
