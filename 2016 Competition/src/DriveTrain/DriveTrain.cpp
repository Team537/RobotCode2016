#include <DriveTrain/DriveTrain.hpp>

void DriveTrain::Update(bool teleop)
{
    float output;
    float target;
    float crossSign;
    float gyroError;

    switch (state)
    {
        case (DriveState::AUTO_ANGLE):
            angleTBH->SetInput(gyro->GetYaw());
            output = angleTBH->GetOutput();

            leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
            rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

            rightDriveMaster->Set(-rightSpeedCurrent);
            leftDriveMaster->Set(leftSpeedCurrent);

            if (fabs(angleTBH->GetError()) < DRIVE_ANGLE_TOLERENCE || stateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
            }
            break;
        case (DriveState::AUTO_DISTANCE):
            if (fabs(rightDriveMaster->GetEncPosition() - rightDriveMaster->GetSetpoint()) < DRIVE_DISTANCE_TOLERENCE ||
                fabs(leftDriveMaster->GetEncPosition() - leftDriveMaster->GetSetpoint()) < DRIVE_DISTANCE_TOLERENCE ||
                stateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
            }
            return;
        case (DriveState::CROSSING):
            crossSign = crossReverse ? -1.0f : 1.0f;
            gyroError = gyro->GetYaw();
            rightSpeedCurrent = 1.0f;
            leftSpeedCurrent = 1.0f;
            DefenceCross();

            if (abs(gyroError) > 3)
            {
                if (gyroError > 0)
                {
                    leftSpeedCurrent -= gyroError * (1.0f / 180.0f) * 0.01f;
                    leftSpeedCurrent = leftSpeedCurrent < 0 ? leftSpeedCurrent : 0;
                }

                if (gyroError < 0)
                {
                    rightSpeedCurrent += gyroError * (1.0f / 180.0f) * 0.01f;
                    rightSpeedCurrent = rightSpeedCurrent < 0 ? rightSpeedCurrent : 0;
                }
            }

            rightSpeedCurrent *= 500 * crossSign * DRIVE_DEFENCE_MULTIPLIER;
            leftSpeedCurrent *= -500 * crossSign * DRIVE_DEFENCE_MULTIPLIER;

            // Set the talon speeds.
            rightDriveMaster->Set(crossReverse ? -leftSpeedCurrent : rightSpeedCurrent);
            leftDriveMaster->Set(crossReverse ? -rightSpeedCurrent : leftSpeedCurrent);

            if (hasCrossed || stateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
            }
            break;
        case (DriveState::TELEOP_CONTROL):
            leftSpeedCurrent = (isClimbing ? joystickSecondary : joystickPrimary)->GetRawAxis(JOYSTICK_AXIS_LEFT_Y);
            rightSpeedCurrent = (isClimbing ? joystickSecondary : joystickPrimary)->GetRawAxis(JOYSTICK_AXIS_RIGHT_Y);

            // Deadband
            if (fabs(leftSpeedCurrent) < CONTROLLER_DEADBAND)
            {
                leftSpeedCurrent = 0;
            }

            if (fabs(rightSpeedCurrent) < CONTROLLER_DEADBAND)
            {
                rightSpeedCurrent = 0;
            }

            leftSpeedCurrent *= DRIVE_SPEED_MULTIPLIER * (isClimbing ? DRIVE_CLIMBING_MULTIPLIER : 1.0f);
            rightSpeedCurrent *= DRIVE_SPEED_MULTIPLIER * (isClimbing ? DRIVE_CLIMBING_MULTIPLIER : 1.0f);

            if (shiftLow->WasDown())
            {
                Shift(false);
            }
            else if (shiftHigh->WasDown())
            {
                Shift(true);
            }

            if (joystickPrimary->GetPOV() != -1.0f)
            {
                AutoAngle(joystickPrimary->GetPOV());
            }
            else if (autoCrossToggle->GetState() && fabs(leftSpeedCurrent) > CONTROLLER_DEADBAND)
            {
                Cross(leftSpeedCurrent > CONTROLLER_DEADBAND);
            }
            else
            {
                rightDriveMaster->Set(-rightSpeedCurrent);
                leftDriveMaster->Set(leftSpeedCurrent);
            }
            break;
        case (DriveState::TELEOP_SHOOT):
            target = (vision->GetGoalCenterX() / WEBCAM_PIXEL_WIDTH) * 2 - 1;
            visionPIDSource->SetPIDTarget(target);
            visionPID->SetSetpoint(0);

            output = visionPIDOutput->GetOutput();
            leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
            rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

            rightDriveMaster->Set(-rightSpeedCurrent);
            leftDriveMaster->Set(leftSpeedCurrent);

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
    SmartDashboard::PutBoolean("Drive High Gear", shifter->Get());

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

    SmartDashboard::PutString("Drive State", state == CROSSING ? "Crossing" : state == TELEOP_SHOOT ? "Teleop Shooter" : state == AUTO_ANGLE ? "Auto Angle" : state == AUTO_DISTANCE ? "Auto Distance" : state == TELEOP_CONTROL ? "Teleop Control" : "None");

    LiveWindow::GetInstance()->AddSensor("Drive", "VisionPID", visionPID);
}

void DriveTrain::SetState(DriveState driveState)
{
    state = driveState;

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
        rightDriveMaster->SetF(0.9f);

        leftDriveMaster->SetPID(0.24f, 0.0f, 0.0f);
        leftDriveMaster->SetF(0.9f);

        hasCrossed = false;
        crossState = 0;
    }
    else
    {
        rightDriveMaster->SetControlMode(CANTalon::ControlMode::kPercentVbus);
        leftDriveMaster->SetControlMode(CANTalon::ControlMode::kPercentVbus);

        rightDriveMaster->SetPID(0.0f, 0.0f, 0.0f);
        leftDriveMaster->SetPID(0.0f, 0.0f, 0.0f);
    }

    if (state == DriveState::TELEOP_SHOOT)
    {
        visionPID->Enable();
    }
    else
    {
        visionPID->Disable();
    }

    if (state == DriveState::AUTO_ANGLE)
    {
        angleTBH->Enable();
    }
    else
    {
        angleTBH->Disable();
    }

    if (state == DriveState::TELEOP_CONTROL)
    {
        rightDriveMaster->SetVoltageRampRate(32.0f);
        leftDriveMaster->SetVoltageRampRate(32.0f);
    }
    else
    {
        rightDriveMaster->SetVoltageRampRate(24.0f);
        leftDriveMaster->SetVoltageRampRate(24.0f);
    }

    rightDriveMaster->Enable();
    leftDriveMaster->Enable();

    rightDriveMaster->SetPosition(0);
    leftDriveMaster->SetPosition(0);

    if (state == DriveState::AUTO_ANGLE || state == DriveState::AUTO_DISTANCE || state == DriveState::CROSSING)
    {
        Shift(false);
    }
}

void DriveTrain::Shift(bool highGear)
{
    shifter->Set(highGear);
}

void DriveTrain::AutoAngle(float angleDegrees)
{
    SetState(DriveState::AUTO_ANGLE);
    gyro->Reset();

    float targetAngle = angleDegrees;

    if (targetAngle > 180)
    {
        targetAngle -= 360;
    }

    angleTBH->SetTarget(targetAngle);
}

void DriveTrain::AutoDistance(int distanceIn)
{
    SetState(DriveState::AUTO_DISTANCE);
    targetDistance = round(distanceIn * DRIVE_FT_TO_ENCODER);
    rightDriveMaster->Set(targetDistance);
    leftDriveMaster->Set(-targetDistance);
}

void DriveTrain::SetCrossing(bool crossing)
{
    isClimbing = crossing;
}

bool DriveTrain::IsWaiting()
{
    return state == DriveState::NONE;
}

void DriveTrain::Cross(bool reverse)
{
    SetState(DriveState::CROSSING);
    crossReverse = reverse;
    gyro->ZeroYaw();
}

float DriveTrain::GetCurrentDraw()
{
    return (rightDriveMaster->GetOutputCurrent() + rightDriveSlave1->GetOutputCurrent() + rightDriveSlave2->GetOutputCurrent() + leftDriveMaster->GetOutputCurrent() + leftDriveSlave1->GetOutputCurrent() + leftDriveSlave2->GetOutputCurrent()) / 6.0f;
}
