#include <DriveTrain/DriveTrain.hpp>

void DriveTrain::Update(bool teleop)
{
    float output;
    //float target;
    float speedMultiplier;
    float gyroError;

    switch (state)
    {
        case (DriveState::AUTO_ANGLE):
            output = 0;
            leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
            rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

            if (IsAtAngle() || distUntoggle->WasDown()) // || teleop
            {
                SetState(DriveState::NONE);
            }
            break;
        case (DriveState::AUTO_DISTANCE):
            if (IsAtDistance() || distUntoggle->WasDown()) // || teleop
            {
                SetState(DriveState::NONE);
            }
            return;
        case (DriveState::CROSSING):
            gyroError = gyro->GetYaw();
            rightSpeedCurrent = 1.0f;
            leftSpeedCurrent = 1.0f;

            if (abs(gyroError) > 3)
            {
                if (gyroError > 0)
                {
                    leftSpeedCurrent -= gyroError * (1/180.0f) * 0.01f;
                    leftSpeedCurrent = leftSpeedCurrent < 0 ? leftSpeedCurrent : 0;
                }
                if (gyroError < 0)
                {
                    rightSpeedCurrent += gyroError * (1/180.0f) * 0.01f;
                    rightSpeedCurrent = rightSpeedCurrent < 0 ? rightSpeedCurrent : 0;
                }
            }

            // Set the talon speeds.
            rightDrive1->Set(rightSpeedCurrent * 500);
            leftDrive4->Set(-leftSpeedCurrent * 500);

            if (distUntoggle->WasDown())
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

            if (distanceToggle->WasDown())
            {
                // AutoDistance(5 * 12.0f);
                Cross();
            }
            else
            {
                // Set the talon speeds.
                rightDrive1->Set(-rightSpeedCurrent);
                leftDrive4->Set(leftSpeedCurrent);
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

    SmartDashboard::PutNumber("Drive Setpoint Right", rightDrive1->GetSetpoint());
    SmartDashboard::PutNumber("Drive Setpoint Left", leftDrive4->GetSetpoint());

    SmartDashboard::PutNumber("Drive Encoder Speed Left", leftDrive4->GetSpeed());
    SmartDashboard::PutNumber("Drive Encoder Speed Right", rightDrive1->GetSpeed());

    SmartDashboard::PutNumber("Drive Encoder Right", -rightDrive1->GetEncPosition());
    SmartDashboard::PutNumber("Drive Encoder Left", leftDrive4->GetEncPosition());

    SmartDashboard::PutNumber("Drive Cross Angle Error", gyro->GetYaw());

    SmartDashboard::PutNumber("Drive Draw Average", GetCurrentDraw());

    SmartDashboard::PutBoolean("Sucsessful Cross", haveCrossed);
    SmartDashboard::PutNumber("Crossing State",CrossState);

    SmartDashboard::PutString("Drive State", state == CROSSING ? "Crossing" : state == TELEOP_SHOOT ? "Teleop Shooter" : state == AUTO_ANGLE ? "Auto Angle" : state == AUTO_DISTANCE ? "Auto Distance" : state == TELEOP_CONTROL ? "Teleop Control" : "None");
}

void DriveTrain::SetState(DriveState driveState)
{
    state = driveState;

    if (state == DriveState::AUTO_DISTANCE || state == DriveState::TELEOP_SHOOT)
    {
        rightDrive1->SetControlMode(CANTalon::ControlMode::kPosition);
        leftDrive4->SetControlMode(CANTalon::ControlMode::kPosition);

        rightDrive1->SetPID(0.085f, 0.0f, 0.0f);
        leftDrive4->SetPID(0.085f, 0.0f, 0.0f);
    }
    else if (state == DriveState::CROSSING)
    {
        rightDrive1->SetControlMode(CANTalon::ControlMode::kSpeed);
        leftDrive4->SetControlMode(CANTalon::ControlMode::kSpeed);

        rightDrive1->SetPID(0.24f, 0.0f, 0.0f);
        rightDrive1->SetF(0.9f);

        leftDrive4->SetPID(0.24f, 0.0f, 0.0f);
        leftDrive4->SetF(0.9f);
    }
    else
    {
        rightDrive1->SetControlMode(CANTalon::ControlMode::kPercentVbus);
        leftDrive4->SetControlMode(CANTalon::ControlMode::kPercentVbus);

        rightDrive1->SetPID(0.0f, 0.0f, 0.0f);
        leftDrive4->SetPID(0.0f, 0.0f, 0.0f);
    }

    if (state == DriveState::TELEOP_CONTROL)
    {
        rightDrive1->SetVoltageRampRate(32.0f);
        leftDrive4->SetVoltageRampRate(32.0f);
    }
    else
    {
        rightDrive1->SetVoltageRampRate(24.0f);
        leftDrive4->SetVoltageRampRate(24.0f);
    }

    rightDrive1->Enable();
    leftDrive4->Enable();

    rightDrive1->SetPosition(0);
    leftDrive4->SetPosition(0);

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

    rightDrive1->Set(driveDistance);
    leftDrive4->Set(-driveDistance);
}

bool DriveTrain::IsWaiting()
{
    return state == DriveState::NONE;
}

bool DriveTrain::IsAtAngle()
{
    return true; // TODO
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

float DriveTrain::GetCurrentDraw()
{
    return (rightDrive1->GetOutputCurrent() + rightDrive2->GetOutputCurrent() + rightDrive3->GetOutputCurrent() + leftDrive4->GetOutputCurrent() + leftDrive5->GetOutputCurrent() + leftDrive6->GetOutputCurrent()) / 6.0f;
}

bool DriveTrain::DefenceCross()
{
    switch(CrossState){
        case 0:
            haveCrossed = false;
            if(gyro->GetRoll() >= -7.0f)
            {
                CrossState = 1;
            }
            break;
        case 1:
           if(gyro->GetRoll() >= 7.0f)
           {
               CrossTime->Start();
               CrossState = 2;
           }
           break;
        case 2:
            if(fabs(gyro->GetRoll()) >= 4)
            {
                CrossTime->Stop();
                CrossTime->Reset();
                CrossState = 3;
            }
            if(CrossTime->Get() >=2)
            {
                CrossTime->Stop();
                CrossTime->Reset();
                CrossState = 4;
            }
            break;
        case 3:
            if(fabs(gyro->GetRoll()) <= 4)
            {
                CrossTime->Start();
                CrossState = 2;
            }
            break;
        case 4:
            haveCrossed = true;
            break;
    }
    return haveCrossed;
}
