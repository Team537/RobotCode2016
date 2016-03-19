#include <DriveTrain/DriveTrain.hpp>

void DriveTrain::Update(const bool& teleop)
{
    float output;
    float target;
    float crossSign;
    float gyroError;

    if (joystickPrimary->GetRawAxis(JOYSTICK_AXIS_RIGHT_Y) > JOYSTICK_DEADBAND || joystickPrimary->GetRawAxis(JOYSTICK_AXIS_RIGHT_Y) > JOYSTICK_DEADBAND)
    {
        primaryDriving = true;
    }
    else
    {
        primaryDriving = false;
    }

    // Secondary update checks!
    if (!isClimbing)
    {
        if (joystickSecondary->GetPOV() != -1.0f)
        {
            crossingForward = joystickSecondary->GetPOV() == 0 ? true : joystickSecondary->GetPOV() == 180 ? false : crossingForward;
        }

        if (joystickSecondary->GetRawButton(JOYSTICK_Y))
        {
            crossSpeedMultiplier = DRIVE_DEFENSE_LOW_BAR;
        }
        else if (joystickSecondary->GetRawButton(JOYSTICK_X))
        {
            crossSpeedMultiplier = DRIVE_DEFENSE_RAMP_PARTS;
        }
        else if (joystickSecondary->GetRawButton(JOYSTICK_B))
        {
            crossSpeedMultiplier = DRIVE_DEFENSE_MOAT;
        }
        else if (joystickSecondary->GetRawButton(JOYSTICK_A))
        {
            crossSpeedMultiplier = DRIVE_DEFENSE_ROCK_WALL;
        }
    }

    switch (state)
    {
        case (DriveState::AUTO_ANGLE):
            // Updates the ETC input and grabs the output.
            angleETC->SetInput(gyro->GetYaw());
            output = angleETC->GetOutput();

            // Calculated what direction the output want to go.
            leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
            rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

            // Drives the master talons.
            rightDriveMaster->Set(-rightSpeedCurrent);
            leftDriveMaster->Set(leftSpeedCurrent);

            // If on target or untoggled, go to state NONE.
            if (fabs(angleETC->GetError()) < DRIVE_ANGLE_TOLERANCE || stateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
            }
            break;
        case (DriveState::AUTO_DISTANCE):
            // If at target or untoggled, go to state NONE.
            if (fabs(rightDriveMaster->GetEncPosition() - rightDriveMaster->GetSetpoint()) < DRIVE_DISTANCE_TOLERANCE || fabs(leftDriveMaster->GetEncPosition() - leftDriveMaster->GetSetpoint()) < DRIVE_DISTANCE_TOLERANCE || stateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
            }
            return;
        case (DriveState::AUTO_TIMED):
            rightDriveMaster->Set(-1 * DRIVE_TIMED_SPEED);
            leftDriveMaster->Set(1 * DRIVE_TIMED_SPEED);
            break;
        case (DriveState::CROSSING):
            // Update the current readings and errors.
            crossSign = crossReverse ? 1.0f : -1.0f;
            gyroError = gyro->GetYaw();
            rightSpeedCurrent = 1.0f;
            leftSpeedCurrent = 1.0f;
            DefenceCross();

            // Figures out how much to offset drive for gyro angle correction.
            if (abs(gyroError) > 3)
            {
                if (gyroError < 0)
                {
                    leftSpeedCurrent -= gyroError * (1.0f / 180.0f) * 0.01f;
                    leftSpeedCurrent = leftSpeedCurrent < 0 ? leftSpeedCurrent : 0;
                }

                if (gyroError > 0)
                {
                    rightSpeedCurrent += gyroError * (1.0f / 180.0f) * 0.01f;
                    rightSpeedCurrent = rightSpeedCurrent < 0 ? rightSpeedCurrent : 0;
                }
            }

            // Swap signs before set.
            rightSpeedCurrent *= 350 * crossSign * crossSpeedMultiplier;
            leftSpeedCurrent *= -350 * crossSign * crossSpeedMultiplier;

            // Drives the master talons.
            rightDriveMaster->Set(crossReverse ? -leftSpeedCurrent : rightSpeedCurrent);
            leftDriveMaster->Set(crossReverse ? -rightSpeedCurrent : leftSpeedCurrent);

            // If has crossed or untoggled, go to state NONE.
            if (hasCrossed || stateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
                crossSpeedMultiplier = 1.0f;
                crossingForward = true;
            }
            break;
        case (DriveState::TELEOP_CONTROL):
            // Shifts the gears.
            if (shiftLow->WasDown())
            {
                Shift(false);
            }
            else if (shiftHigh->WasDown())
            {
                Shift(true);
            }

            if (reverseToggle->WasDown())
            {
                reverse = !reverse;
            }

            // Grabs the current speed from the two drive axes.
            leftSpeedCurrent = (isClimbing && !primaryDriving ? joystickSecondary : joystickPrimary)->GetRawAxis(!reverse ? JOYSTICK_AXIS_LEFT_Y : JOYSTICK_AXIS_RIGHT_Y);
            rightSpeedCurrent = (isClimbing && !primaryDriving ? joystickSecondary : joystickPrimary)->GetRawAxis(!reverse ? JOYSTICK_AXIS_RIGHT_Y : JOYSTICK_AXIS_LEFT_Y);

            // Deadband
            if (fabs(leftSpeedCurrent) < JOYSTICK_DEADBAND)
            {
                leftSpeedCurrent = 0;
            }

            if (fabs(rightSpeedCurrent) < JOYSTICK_DEADBAND)
            {
                rightSpeedCurrent = 0;
            }

            // Multiplies the speed to slow down the bot.
            leftSpeedCurrent *= DRIVE_SPEED_MULTIPLIER * (isClimbing ? DRIVE_CLIMBING_MULTIPLIER : 1.0f);
            rightSpeedCurrent *= DRIVE_SPEED_MULTIPLIER * (isClimbing ? DRIVE_CLIMBING_MULTIPLIER : 1.0f);

            // Gets the auto angle from POV (if down).
            if (joystickPrimary->GetPOV() != -1.0f)
            {
                AutoAngle(joystickPrimary->GetPOV());
            }
            // Auto crosses if toggle is down!
            else if (autoCrossToggle->GetState())
            {
                Cross(crossingForward, crossSpeedMultiplier);
            }
            // Drives the master talons.
            else
            {
                rightDriveMaster->Set(reverse /*&& primaryDriving*/ ? rightSpeedCurrent : -rightSpeedCurrent);
                leftDriveMaster->Set(reverse /*&& primaryDriving*/ ? -leftSpeedCurrent : leftSpeedCurrent);
            }
            break;
        case (DriveState::TELEOP_SHOOT):
            // Gets the goal in view coords of -0.5 to 0.5.
            target = (vision->GetGoalCenterX() / WEBCAM_PIXEL_WIDTH) * 2 - 1;
            visionPIDSource->SetPIDTarget(target);
            visionPID->SetSetpoint(0);

            // Grabs the output direction to turn
            output = visionPIDOutput->GetOutput();

            // Calculated what direction the output want to go.
            leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
            rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

            // Drives the master talons.
            rightDriveMaster->Set(-rightSpeedCurrent);
            leftDriveMaster->Set(leftSpeedCurrent);

            // If on vision target or untoggled, go to state NONE.
            if (visionPID->OnTarget() || stateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
            }
            break;
        case (DriveState::NONE):
            if (teleop)
            {
                SetState(DriveState::TELEOP_CONTROL);
            }
            else
            {
                rightDriveMaster->Set(0);
                leftDriveMaster->Set(0);
            }
            break;
    }
}

bool DriveTrain::DefenceCross()
{
    switch (crossState)
    {
        case 0:
            hasCrossed = false;

            if (gyro->GetRoll() >= -7.0f)
            {
                crossState = 1;
            }
            break;
        case 1:
            if (gyro->GetRoll() >= 7.0f)
            {
                crossTime->Reset();
                crossTime->Start();
                crossState = 2;
            }
            break;
        case 2:
            if (fabs(gyro->GetRoll()) >= 4)
            {
                crossTime->Stop();
                crossState = 3;
            }

            if (crossTime->Get() >= 1)
            {
                crossTime->Stop();
                crossState = 4;
            }
            break;
        case 3:
            if (fabs(gyro->GetRoll()) <= 4)
            {
                crossTime->Start();
                crossState = 2;
            }
            break;
        case 4:
            hasCrossed = true;
            break;
    }

    return hasCrossed;
}

void DriveTrain::Dashboard()
{
    SmartDashboard::PutNumber("Drive Speed Left", leftSpeedCurrent);
    SmartDashboard::PutNumber("Drive Speed Right", rightSpeedCurrent);
    SmartDashboard::PutBoolean("Drive High Gear", shift->Get());

    SmartDashboard::PutBoolean("Drive Cross Forward", crossingForward);
    SmartDashboard::PutNumber("Drive Cross Multiplier", crossSpeedMultiplier);

    SmartDashboard::PutNumber("Drive Angle Target", visionPIDSource->PIDGet());
    SmartDashboard::PutNumber("Drive Angle PID Out", visionPIDOutput->GetOutput());

    SmartDashboard::PutNumber("Drive Setpoint Right", rightDriveMaster->GetSetpoint());
    SmartDashboard::PutNumber("Drive Setpoint Left", leftDriveMaster->GetSetpoint());

    SmartDashboard::PutNumber("Drive Encoder Speed Left", leftDriveMaster->GetSpeed());
    SmartDashboard::PutNumber("Drive Encoder Speed Right", rightDriveMaster->GetSpeed());

    SmartDashboard::PutNumber("Drive Encoder Right", -rightDriveMaster->GetEncPosition());
    SmartDashboard::PutNumber("Drive Encoder Left", leftDriveMaster->GetEncPosition());

    SmartDashboard::PutNumber("Drive Draw Average", GetCurrentDraw());

    SmartDashboard::PutBoolean("Drive Cross Successful", hasCrossed);
    SmartDashboard::PutNumber("Drive Cross State", crossState);

    SmartDashboard::PutString("Drive State", stateNames[state]);

    SmartDashboard::PutBoolean("Drive Reversed", reverse);

    LiveWindow::GetInstance()->AddSensor("Drive", "VisionPID", visionPID);
}

void DriveTrain::SetState(DriveState driveState)
{
    state = driveState;

    // Sets the talons contol modes.
    if (state == DriveState::AUTO_DISTANCE)
    {
        rightDriveMaster->SetControlMode(CANTalon::ControlMode::kPosition);
        leftDriveMaster->SetControlMode(CANTalon::ControlMode::kPosition);

        rightDriveMaster->SetPID(0.085f, 0.0f, 0.0f);
        leftDriveMaster->SetPID(0.085f, 0.0f, 0.0f);
    }
    else if (state == DriveState::CROSSING)
    {
        rightDriveMaster->SetControlMode(CANTalon::ControlMode::kSpeed);
        leftDriveMaster->SetControlMode(CANTalon::ControlMode::kSpeed);

        rightDriveMaster->SetPID(0.24f, 0.0f, 0.0f);
        rightDriveMaster->SetF(1.8f);

        leftDriveMaster->SetPID(0.24f, 0.0f, 0.0f);
        leftDriveMaster->SetF(1.8f);

        hasCrossed = false;
        crossState = 0;
    }
    else
    {
        rightDriveMaster->SetControlMode(CANTalon::ControlMode::kPercentVbus);
        leftDriveMaster->SetControlMode(CANTalon::ControlMode::kPercentVbus);

        rightDriveMaster->SetPID(0.0f, 0.0f, 0.0f);
        rightDriveMaster->SetF(0.0f);
        leftDriveMaster->SetF(0.0f);
        leftDriveMaster->SetPID(0.0f, 0.0f, 0.0f);
    }

    // Sets voltage ramp rates.
    if (state == DriveState::TELEOP_CONTROL)
    {
        rightDriveMaster->SetVoltageRampRate(36.0f);
        leftDriveMaster->SetVoltageRampRate(36.0f);
    }
    else
    {
        rightDriveMaster->SetVoltageRampRate(22.0f);
        leftDriveMaster->SetVoltageRampRate(22.0f);
    }

    // Sets the vision pid's usage.
    if (state == DriveState::TELEOP_SHOOT)
    {
        visionPID->Enable();
    }
    else
    {
        visionPID->Disable();
    }

    // Sets the angle pid's usage.
    if (state == DriveState::AUTO_ANGLE)
    {
        angleETC->Enable();
    }
    else
    {
        angleETC->Disable();
    }

    // Enables the talons.
    rightDriveMaster->Enable();
    leftDriveMaster->Enable();

    // Sets the sensor readings to zero.
    rightDriveMaster->SetPosition(0);
    leftDriveMaster->SetPosition(0);

    // Go's to low gear if not in teleop control.
    if (state != DriveState::TELEOP_CONTROL)
    {
        Shift(false);
    }
}

void DriveTrain::Shift(const bool& highGear)
{
    shift->Set(highGear);
}

void DriveTrain::AutoAngle(const float& angleDegrees)
{
    // Changes the state.
    SetState(DriveState::AUTO_ANGLE);
    // Resets the gyro.
    gyro->Reset();

    // Change angles from 0 to 360 => -180 to 180.
    float targetAngle = angleDegrees;

    if (targetAngle > 180)
    {
        targetAngle -= 360;
    }

    // Sets the angle targets.
    angleETC->SetTarget(targetAngle);
}

void DriveTrain::AutoDistance(const int& distanceIn)
{
    // Changes the state.
    SetState(DriveState::AUTO_DISTANCE);
    // Converts the distance from IN to encoder ticks.
    targetDistance = round(distanceIn * DRIVE_IN_TO_ENCODER);
    // Sets the distance to drive.
    rightDriveMaster->Set(targetDistance);
    leftDriveMaster->Set(-targetDistance);
}

// TODO: Finish timed auto drive.
void DriveTrain::AutoTimed()
{
    SetState(DriveState::AUTO_TIMED);
}

void DriveTrain::SetCrossing(const bool& crossing)
{
    isClimbing = crossing;
}

bool DriveTrain::IsWaiting()
{
    return state == DriveState::NONE;
}

bool DriveTrain::IsTeleopControl()
{
    return state == DriveState::TELEOP_CONTROL;
}

void DriveTrain::Cross(const bool& reverse, const float& speed)
{
    // Changes the state.
    SetState(DriveState::CROSSING);
    // Resets the gyro.
    gyro->Reset();
    // Sets if its crossing in reverse.
    crossReverse = reverse;
    crossSpeedMultiplier = speed;
}

float DriveTrain::GetCurrentDraw()
{
    return (rightDriveMaster->GetOutputCurrent() + rightDriveSlave1->GetOutputCurrent() + rightDriveSlave2->GetOutputCurrent() + leftDriveMaster->GetOutputCurrent() + leftDriveSlave1->GetOutputCurrent() + leftDriveSlave2->GetOutputCurrent()) / 6.0f;
}
