#include <DriveTrain/DriveTrain.hpp>

void DriveTrain::Update(bool teleop)
{
	switch (state)
	{
		float output;

		case (DriveState::GOTO_ANGLE):
			anglePID->Enable();
			anglePID->SetSetpoint(targetAngle);
			anglePIDSource->SetPIDTarget(ahrs->GetAngle() * (1.0f / 360.0f) * 2 - 1);

			output = anglePIDOutput->GetOutput();

			leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
			rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

			if ((!teleop && OnTargetAngle()) || shootButton->WasDown())
			{
				ChangeState(DriveState::NONE);
			}
			break;
		case (DriveState::GOTO_DISTANCE):
			leftSpeedCurrent = leftDrive4->GetSpeed();
			rightSpeedCurrent = rightDrive1->GetSpeed();

			if ((!teleop && OnTargetDistance()) || shootButton->WasDown())
			{
				ChangeState(DriveState::NONE);
			}
			break;
		case (DriveState::TELE_SHOOTER):
			targetAngle = (vision->GetGoalCenterX() / WEBCAM_PIXEL_WIDTH) * 2 - 1;
			anglePIDSource->SetPIDTarget(targetAngle);
			anglePID->SetSetpoint(0);

			output = anglePIDOutput->GetOutput();

			leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
			rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

			if (OnTargetAngle() || shootButton->WasDown())
			{
				ChangeState(DriveState::TELE_CONTROL);
			}
			break;
		case (DriveState::TELE_CONTROL):
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

			if (shootButton->WasDown())
			{
				ChangeState(DriveState::TELE_SHOOTER);
			}

			break;
		case (DriveState::NONE):
			if (teleop)
			{
				state = DriveState::TELE_CONTROL;
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
	rightDrive1->Set(-rightSpeedCurrent);
	leftDrive4->Set(leftSpeedCurrent);
}

void DriveTrain::Dashboard()
{
	SmartDashboard::PutNumber("Drive Speed Left", leftSpeedCurrent);
	SmartDashboard::PutNumber("Drive Speed Right", rightSpeedCurrent);
	SmartDashboard::PutBoolean("Drive In High Gear", shifter->Get());

	SmartDashboard::PutNumber("Drive Angle Target", anglePIDSource->PIDGet());
	SmartDashboard::PutBoolean("Drive Angle On Target", OnTargetAngle());

	SmartDashboard::PutBoolean("Drive Encoder Right", rightDrive1->GetEncPosition());
	SmartDashboard::PutBoolean("Drive Encoder Left", leftDrive4->GetEncPosition());

	SmartDashboard::PutBoolean("Drive Distance Encoder Target", encoderGoal);
	SmartDashboard::PutBoolean("Drive Distance On Target", OnTargetDistance());

	SmartDashboard::PutBoolean("Drive Is Enabled", IsEnabled());

	SmartDashboard::PutNumber("Drive Draw Average", (
			rightDrive1->GetOutputCurrent() + rightDrive2->GetOutputCurrent() + rightDrive3->GetOutputCurrent() +
			leftDrive4->GetOutputCurrent() + leftDrive5->GetOutputCurrent() + leftDrive6->GetOutputCurrent()) / 6.0f);

	SmartDashboard::PutString("Drive State",
			state == TELE_SHOOTER ? "Tele Shooter" :
			state == GOTO_ANGLE ? "GOTO Angle" :
			state == GOTO_DISTANCE ? "GOTO Distance" :
			state == TELE_CONTROL ? "Tele Control" : "None"
	);

	LiveWindow::GetInstance()->AddSensor("DriveTrain", "Angle PID", anglePID);
}

void DriveTrain::ChangeState(DriveState newState)
{
	state = newState;

	switch(state)
	{
		case(DriveState::TELE_SHOOTER):
		case(DriveState::GOTO_ANGLE):
			encoderGoal = 0.0f;
			anglePID->Enable();
			break;
		case(DriveState::GOTO_DISTANCE):
			anglePID->Disable();
			break;
		case(DriveState::TELE_CONTROL):
			encoderGoal = 0.0f;
			anglePID->Disable();
			break;
		case(DriveState::NONE):
			encoderGoal = 0.0f;
			anglePID->Disable();
			break;
	}

	rightDrive1->EnableControl();
	leftDrive4->EnableControl();
}

void DriveTrain::AutoDrive(float distanceFt)
{
	ChangeState(DriveState::GOTO_DISTANCE);
	encoderGoal = distanceFt * DRIVE_FT_TO_ENCODER;

	leftDrive4->Reset();
	rightDrive1->Reset();

	leftDrive4->Set(encoderGoal);
	rightDrive1->Set(encoderGoal);
}

void DriveTrain::AutoAngle(float targetAngle)
{
	ChangeState(DriveState::GOTO_ANGLE);
	this->targetAngle = targetAngle * (1.0f / 360.0f) * 2 - 1;
}

void DriveTrain::Shift(bool highGear)
{
	/*if (state == DriveState::GOTO_DISTANCE && shifter->Get() != highGear)
	{
		float distanceTraveled = ((leftDrive4->GetEncPosition() - encoderGoal) + (rightDrive1->GetEncPosition() - encoderGoal)) / 2.0f;

		// High To Low!
		if (shifter->Get())
		{
			distanceTraveled /= DRIVE_FT_TO_ENCODER_HIGH;
		}
		// Low to high!
		else
		{
			distanceTraveled /= DRIVE_FT_TO_ENCODER_LOW;
		}

		shifter->Set(highGear);
		AutoDrive(distanceTraveled);
	}*/

	shifter->Set(highGear);
}

bool DriveTrain::IsEnabled()
{
	return leftDrive4->IsEnabled() && rightDrive1->IsEnabled();
}

bool DriveTrain::IsWaiting()
{
	return state == DriveState::NONE;
}

bool DriveTrain::OnTargetAngle()
{
	return anglePID->IsEnabled() && anglePID->OnTarget();
}

bool DriveTrain::OnTargetDistance()
{
	return (fabs(leftDrive4->GetEncPosition() - encoderGoal) < DRIVE_DISTANCE_ERROR) && (fabs(rightDrive1->GetEncPosition() - encoderGoal) < DRIVE_DISTANCE_ERROR);
}
