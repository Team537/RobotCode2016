#include <DriveTrain/DriveTrain.hpp>

void DriveTrain::Update(bool teleop)
{
    float output;
    float target;
    float gyroError;

    switch (state)
    {
        case (DriveState::AUTO_ANGLE):
            gyroError = gyro->GetYaw() - targetAngle;
            target = gyroError * (1.0f / 360.0f);
            output = target * (tbhTime->Get() * tbhTime->Get()); // TODO;

            SmartDashboard::PutNumber("Drive TBH Target", targetAngle);
            SmartDashboard::PutNumber("Drive TBH Input", gyro->GetYaw());
            SmartDashboard::PutNumber("Drive TBH Error", gyroError);
            SmartDashboard::PutNumber("Drive TBH Output", output);

            leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
            rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

            rightDriveMaster->Set(-rightSpeedCurrent);
            leftDriveMaster->Set(leftSpeedCurrent);

            if (fabs(gyroError) < DRIVE_ANGLE_TOLERENCE || driveStateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
            }
            break;
        case (DriveState::AUTO_DISTANCE):
            if (fabs(rightDriveMaster->GetEncPosition() - rightDriveMaster->GetSetpoint()) < DRIVE_DISTANCE_TOLERENCE ||
                fabs(leftDriveMaster->GetEncPosition() - leftDriveMaster->GetSetpoint()) < DRIVE_DISTANCE_TOLERENCE ||
                driveStateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
            }
            return;
        case (DriveState::CROSSING):
            gyroError = gyro->GetYaw();
            rightSpeedCurrent = 1.0f;
            leftSpeedCurrent = 1.0f;
            DefenceCross();

            if (abs(gyroError) > 3)
            {
                if (gyroError > 0)
                {
                    leftSpeedCurrent -= gyroError * (1 / 180.0f) * 0.01f;
                    leftSpeedCurrent = leftSpeedCurrent < 0 ? leftSpeedCurrent : 0;
                }
                if (gyroError < 0)
                {
                    rightSpeedCurrent += gyroError * (1 / 180.0f) * 0.01f;
                    rightSpeedCurrent = rightSpeedCurrent < 0 ? rightSpeedCurrent : 0;
                }
            }

            // Set the talon speeds.
            rightDriveMaster->Set(rightSpeedCurrent * 500);
            leftDriveMaster->Set(-leftSpeedCurrent * 500);

            if (hasCrossed || driveStateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
            }
            break;
        case (DriveState::TELEOP_CONTROL):
            leftSpeedCurrent = joystick->GetRawAxis(JOYSTICK_AXIS_LEFT_Y);
            rightSpeedCurrent = joystick->GetRawAxis(JOYSTICK_AXIS_RIGHT_Y);

            // Deadband
            if (fabs(leftSpeedCurrent) < CONTROLLER_DEADBAND)
            {
                leftSpeedCurrent = 0;
            }

            if (fabs(rightSpeedCurrent) < CONTROLLER_DEADBAND)
            {
                rightSpeedCurrent = 0;
            }

            leftSpeedCurrent *= DRIVE_SPEED_MULTIPLIER;
            rightSpeedCurrent *= DRIVE_SPEED_MULTIPLIER;

            if (shiftLow->WasDown())
            {
                Shift(false);
            }
            else if (shiftHigh->WasDown())
            {
                Shift(true);
            }

            if (joystick->GetPOV() != -1.0f)
            {
                AutoAngle(joystick->GetPOV());
            }
            else if (autoCrossToggle->WasDown())
            {
                Cross();
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

            if (visionPID->OnTarget() || driveStateUntoggle->WasDown())
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
    SmartDashboard::PutNumber("Drive Angle Error", gyro->GetYaw());

    SmartDashboard::PutNumber("Drive Setpoint Right", rightDriveMaster->GetSetpoint());
    SmartDashboard::PutNumber("Drive Setpoint Left", leftDriveMaster->GetSetpoint());

    SmartDashboard::PutNumber("Drive Encoder Speed Left", leftDriveMaster->GetSpeed());
    SmartDashboard::PutNumber("Drive Encoder Speed Right", rightDriveMaster->GetSpeed());

    SmartDashboard::PutNumber("Drive Encoder Right", -rightDriveMaster->GetEncPosition());
    SmartDashboard::PutNumber("Drive Encoder Left", leftDriveMaster->GetEncPosition());

    SmartDashboard::PutNumber("Drive Draw Average", GetCurrentDraw());

    SmartDashboard::PutBoolean("Successful Cross", hasCrossed);
    SmartDashboard::PutNumber("Crossing State", crossState);

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
        tbhTime->Reset();
        tbhTime->Start();
    }
    else
    {
        tbhTime->Stop();
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

    targetAngle = angleDegrees;

    if (targetAngle > 180)
    {
        targetAngle -= 360;
    }
}

void DriveTrain::AutoDistance(int distanceIn)
{
    SetState(DriveState::AUTO_DISTANCE);
    targetDistance = round(distanceIn * DRIVE_FT_TO_ENCODER);
    rightDriveMaster->Set(targetDistance);
    leftDriveMaster->Set(-targetDistance);
}

bool DriveTrain::IsWaiting()
{
    return state == DriveState::NONE;
}

void DriveTrain::Cross()
{
    SetState(DriveState::CROSSING);
    gyro->ZeroYaw();
}

float DriveTrain::GetCurrentDraw()
{
    return (rightDriveMaster->GetOutputCurrent() + rightDriveSlave1->GetOutputCurrent() + rightDriveSlave2->GetOutputCurrent() + leftDriveMaster->GetOutputCurrent() + leftDriveSlave1->GetOutputCurrent() + leftDriveSlave2->GetOutputCurrent()) / 6.0f;
}
