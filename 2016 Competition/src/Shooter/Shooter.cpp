#include <Shooter/Shooter.hpp>

void Shooter::Update(bool teleop)
{
    if (teleop)
    {
        if (gotoNoneButton0->WasDown())
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
        if (joystickSecondary->GetRawAxis(JOYSTICK_AXIS_TRIGGER_LEFT) > CONTROLLER_DEADBAND && state != ShooterState::MANUAL)
#else
        if (manualAimButton->WasDown() && state != ShooterState::MANUAL)
#endif
        {
            autoAdvance = false;
            state = ShooterState::AIMING;
        }


        if (flywheelButton->WasDown() && state != ShooterState::MANUAL)
        {
            state = ShooterState::MANUAL;
            talon1->SetControlMode(CANTalon::ControlMode::kPercentVbus);
            talon2->SetControlMode(CANTalon::ControlMode::kPercentVbus);
        }
        if (joystickSecondary->GetRawButton(9)   && state == ShooterState::MANUAL)
        {
            state = ShooterState::NONE;
            talon1->SetControlMode(CANTalon::ControlMode::kSpeed);
            talon2->SetControlMode(CANTalon::ControlMode::kFollower);
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
            double velocity = ((vision->GetGoalDistance() * 0.0254) / cos(WEBCAM_BOT_ANGLE)) * sqrt(G / (2 * (((GOAL_GROUND_HEIGHT - WEBCAM_BOT_HEIGHT) * 0.0254) - (((vision->GetGoalDistance() * 0.0254) * cos(WEBCAM_BOT_ANGLE)) * tan(SHOOTER_ANGLE)))));
            spinSpeed = (velocity * (2 * PI * (0.1 / 2.0)) * 1000.0); // 0.1m diameter, 256 ticks/revolution * 4
        }

            drive->SetState(DriveTrain::DriveState::NONE);

            talon1->Set(spinSpeed);
            //talon2->Set(spinSpeed);

            // Waits until ramped up!
            if ((fabs(talon1->GetEncVel()) < fabs(spinSpeed) + SHOOTER_SPEED_TOLERANCE))// && fabs(talon2->GetSpeed()) > fabs(spinSpeed) - SHOOTER_SPEED_TOLERANCE) && (fabs(talon2->GetEncVel()) < fabs(spinSpeed) + SHOOTER_SPEED_TOLERANCE && fabs(talon2->GetSpeed()) > fabs(spinSpeed) - SHOOTER_SPEED_TOLERANCE))
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
        case ShooterState::MANUAL:
           talon1->Set(-manualSpeed);
           talon2->Set(manualSpeed);
           if (joystickSecondary->GetRawButton(JOYSTICK_BUMPER_RIGHT))
            {
                extendSolenoid->Set(true);
            }
            if (joystickSecondary->GetRawButton(JOYSTICK_BUMPER_LEFT))
            {
                extendSolenoid->Set(false);
            }

            if (joystickSecondary->GetRawAxis(JOYSTICK_AXIS_TRIGGER_RIGHT) > CONTROLLER_DEADBAND)
            {
                manualSpeed +=.05;
            }
            if(joystickSecondary->GetRawAxis(JOYSTICK_AXIS_TRIGGER_LEFT) > CONTROLLER_DEADBAND){
                manualSpeed -=.05;
            }

            if (manualSpeed > 1)
            {
                manualSpeed = 1;
            }
            if (manualSpeed < 0)
            {
                manualSpeed = 0;
            }
            if (flywheelButton->WasDown() )//&& state == ShooterState::MANUAL)
            {
                state = ShooterState::NONE;
                talon1->SetControlMode(CANTalon::ControlMode::kSpeed);
                talon2->SetControlMode(CANTalon::ControlMode::kFollower);
            }
            break;
        case ShooterState::NONE:
            // Returns to states before.
            talon1->Set(0);
            //talon2->Set(0);
            extendSolenoid->Set(false);
            break;
    }

    if (spinSpeed > 1)
    {
        spinSpeed = 1;
    }
    if (spinSpeed < 1)
    {
        spinSpeed = 1;
    }
}

void Shooter::Dashboard()
{
    SmartDashboard::PutString("Shooter State", state == AIMING ? "Aiming" : state == SPINNING ? "Spinning" : state == FIRE ? "Firing" : state == MANUAL ? "Manual" : "None");
    SmartDashboard::PutBoolean("Shooter Activated", IsActivated());
    SmartDashboard::PutBoolean("Shooter Speed", spinSpeed);
    SmartDashboard::PutBoolean("Shooter Encoder", spinSpeed);
    SmartDashboard::PutNumber("Shooter Flywheel Speed", manualSpeed);
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
