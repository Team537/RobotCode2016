#include <DriveTrain/DriveTrain.hpp>

void DriveTrain::Update(bool teleop)
{
    float output;
    //float target;

    switch (state)
    {
        case (DriveState::AUTO_ANGLE):
            output = 0;
            leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
            rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

            if (IsAtAngle() || teleop)
            {
                SetState(DriveState::NONE);
            }
            break;
        case (DriveState::AUTO_DISTANCE):
            // leftSpeedCurrent = speedLeftOutput->Get();
            // rightSpeedCurrent = speedRightOutput->Get();

            if (IsAtDistance() || teleop)
            {
                SetState(DriveState::NONE);
            }
            return;
        case (DriveState::TELEOP_CONTROL):
            leftSpeedCurrent = joystick->GetRawAxis(JOYSTICK_AXIS_LEFT_Y);
            rightSpeedCurrent = joystick->GetRawAxis(JOYSTICK_AXIS_RIGHT_Y);

            if (shiftLow->WasDown())
            {
                Shift(false);
            }
            else if (shiftHigh->WasDown())
            {
                Shift(true);
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

    // Deadband
    if (fabs(leftSpeedCurrent) < CONTROLLER_DEADBAND)
    {
        leftSpeedCurrent = 0;
    }

    if (fabs(rightSpeedCurrent) < CONTROLLER_DEADBAND)
    {
        rightSpeedCurrent = 0;
    }

    // Ramping.
    leftSpeedDelta = leftSpeedCurrent - leftSpeedOld;
    leftSpeedDelta = rightSpeedCurrent - rightSpeedOld;
    leftDriveSign = leftSpeedCurrent / fabs(leftSpeedCurrent);
    rightDriveSign = rightSpeedCurrent / fabs(rightSpeedCurrent);

    if (fabs(leftSpeedDelta) > DRIVE_RAMP_SPEED)
    {
        leftSpeedCurrent = leftSpeedOld + leftDriveSign * DRIVE_RAMP_SPEED;
    }

    if (fabs(rightSpeedDelta) > DRIVE_RAMP_SPEED)
    {
        rightSpeedCurrent = rightSpeedOld + rightDriveSign * DRIVE_RAMP_SPEED;
    }

    float speedMultiplier = (rockWallToggle->GetState() ? DRIVE_SPEED_ROCK_WALL : roughTerrainToggle->GetState() ? DRIVE_SPEED_ROUGH_TERRAIN : 1.0f);
    leftSpeedCurrent *= DRIVE_SPEED_MULTIPLIER * speedMultiplier;
    rightSpeedCurrent *= DRIVE_SPEED_MULTIPLIER * speedMultiplier;

    // Clamping.
    if (fabs(leftSpeedCurrent) > 1)
    {
        leftSpeedCurrent = leftDriveSign;
    }

    if (fabs(rightSpeedCurrent) > 1)
    {
        rightSpeedCurrent = rightDriveSign;
    }

    // Log the left and right speeds.
    leftSpeedOld = leftSpeedCurrent;
    rightSpeedOld = rightSpeedCurrent;

    // Set the talon speeds.
    //rightDrive1->Set(-rightSpeedCurrent);
  //  leftDrive4->Set(leftSpeedCurrent);
}

void DriveTrain::Dashboard()
{
    SmartDashboard::PutNumber("Drive Speed Left", leftSpeedCurrent);
    SmartDashboard::PutNumber("Drive Speed Right", rightSpeedCurrent);
    SmartDashboard::PutBoolean("Drive High Gear", shifter->Get());

    SmartDashboard::PutNumber("Drive Draw Average", GetCurrentDraw());

    SmartDashboard::PutString("Drive State",
            state == TELEOP_SHOOT ? "Teleop Shooter" :
            state == AUTO_ANGLE ? "Auto Angle" :
            state == AUTO_DISTANCE ? "Auto Distance" :
            state == TELEOP_CONTROL ? "Teleop Control" : "None"
    );
}

void DriveTrain::SetState(DriveState driveState)
{
    state = driveState;

    if (state == DriveState::AUTO_DISTANCE)
    {
        rightDrive1->SetControlMode(CANTalon::ControlMode::kPosition);
        leftDrive4->SetControlMode(CANTalon::ControlMode::kPosition);
        rightDrive1->Enable();
        leftDrive4->Enable();
    }
    else
    {
        rightDrive1->SetControlMode(CANTalon::ControlMode::kPercentVbus);
        leftDrive4->SetControlMode(CANTalon::ControlMode::kPercentVbus);
    }

    if (state == DriveState::AUTO_ANGLE || state == DriveState::TELEOP_SHOOT)
    {
        // TODO
    }
    else
    {
        // TODO
    }

    if (state == DriveState::AUTO_ANGLE || state == DriveState::AUTO_DISTANCE)
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

void DriveTrain::distanceTuning()
{
    if (distanceToggle)
    {
        AutoDistance(454);
    }
    else
    {
        AutoDistance(0);
    }
}

void DriveTrain::AutoDistance(float distanceIn)
{
    SetState(DriveState::AUTO_DISTANCE);
    driveDistance = distanceIn;// * ENCODER_SCALAR;
    rightDrive1->Set(driveDistance);
    leftDrive4->Set(driveDistance);
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

float DriveTrain::GetCurrentDraw()
{
    return (rightDrive1->GetOutputCurrent() + rightDrive2->GetOutputCurrent() + rightDrive3->GetOutputCurrent() + leftDrive4->GetOutputCurrent() + leftDrive5->GetOutputCurrent() + leftDrive6->GetOutputCurrent()) / 6.0f;
}
