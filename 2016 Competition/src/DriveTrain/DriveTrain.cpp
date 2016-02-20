#include <DriveTrain/DriveTrain.hpp>

void DriveTrain::Update(bool teleop)
{
    float output;
    float speedMultiplier;
    float gyroError;

    switch (state)
    {
        case (DriveState::AUTO_ANGLE):
            output = 0;
            leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
            rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

            if (IsAtAngle() || driveStateUntoggle->WasDown())
            {
                SetState(DriveState::NONE);
            }
            break;
        case (DriveState::AUTO_DISTANCE):
            if (IsAtDistance() || driveStateUntoggle->WasDown())
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

            if (HasCrossed() || driveStateUntoggle->WasDown())
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

            speedMultiplier = (rockWallToggle->GetState() ? DRIVE_SPEED_ROCK_WALL : roughTerrainToggle->GetState() ? DRIVE_SPEED_ROUGH_TERRAIN : 1.0f);
            leftSpeedCurrent *= DRIVE_SPEED_MULTIPLIER * speedMultiplier;
            rightSpeedCurrent *= DRIVE_SPEED_MULTIPLIER * speedMultiplier;

            if (shiftLow->WasDown())
            {
                Shift(false);
            }
            else if (shiftHigh->WasDown())
            {
                Shift(true);
            }

            if (autoCrossToggle->WasDown())
            {
                Cross();
            }
            else
            {
                // Set the talon speeds.
                rightDriveMaster->Set(-rightSpeedCurrent);
                leftDriveMaster->Set(leftSpeedCurrent);
            }
            break;
        case (DriveState::TELEOP_SHOOT):
            output = 0;
            leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
            rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);
            break;
        case (DriveState::NONE):
            if (teleop)
            {
                SetState(DriveState::TELEOP_CONTROL);
            }
            break;
    }
}

void DriveTrain::Dashboard()
{
    SmartDashboard::PutNumber("Drive Speed Left", leftSpeedCurrent);
    SmartDashboard::PutNumber("Drive Speed Right", rightSpeedCurrent);
    SmartDashboard::PutBoolean("Drive High Gear", shifter->Get());

    SmartDashboard::PutNumber("Drive Setpoint Right", rightDriveMaster->GetSetpoint());
    SmartDashboard::PutNumber("Drive Setpoint Left", leftDriveMaster->GetSetpoint());

    SmartDashboard::PutNumber("Drive Encoder Speed Left", leftDriveMaster->GetSpeed());
    SmartDashboard::PutNumber("Drive Encoder Speed Right", rightDriveMaster->GetSpeed());

    SmartDashboard::PutNumber("Drive Encoder Right", -rightDriveMaster->GetEncPosition());
    SmartDashboard::PutNumber("Drive Encoder Left", leftDriveMaster->GetEncPosition());

    SmartDashboard::PutNumber("Drive Cross Angle Error", gyro->GetYaw());

    SmartDashboard::PutNumber("Drive Draw Average", GetCurrentDraw());

    SmartDashboard::PutBoolean("Successful Cross", hasCrossed);
    SmartDashboard::PutNumber("Crossing State", crossState);

    SmartDashboard::PutString("Drive State", state == CROSSING ? "Crossing" : state == TELEOP_SHOOT ? "Teleop Shooter" : state == AUTO_ANGLE ? "Auto Angle" : state == AUTO_DISTANCE ? "Auto Distance" : state == TELEOP_CONTROL ? "Teleop Control" : "None");
}

void DriveTrain::SetState(DriveState driveState)
{
    state = driveState;

    if (state == DriveState::AUTO_DISTANCE || state == DriveState::TELEOP_SHOOT)
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
    // TODO
}

void DriveTrain::AutoDistance(int distanceIn)
{
    SetState(DriveState::AUTO_DISTANCE);
    driveDistance = round(distanceIn * DRIVE_FT_TO_ENCODER);

    rightDriveMaster->Set(driveDistance);
    leftDriveMaster->Set(-driveDistance);
}

bool DriveTrain::IsWaiting()
{
    return state == DriveState::NONE;
}

bool DriveTrain::IsAtAngle()
{
    return false; // TODO
}

bool DriveTrain::IsAtDistance()
{
    return false; // TODO
}

void DriveTrain::Cross()
{
    SetState(DriveState::CROSSING);
    gyro->ZeroYaw();
}

bool DriveTrain::HasCrossed()
{
    return hasCrossed;
}

float DriveTrain::GetCurrentDraw()
{
    return (rightDriveMaster->GetOutputCurrent() + rightDriveSlave1->GetOutputCurrent() + rightDriveSlave2->GetOutputCurrent() + leftDriveMaster->GetOutputCurrent() + leftDriveSlave1->GetOutputCurrent() + leftDriveSlave2->GetOutputCurrent()) / 6.0f;
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
