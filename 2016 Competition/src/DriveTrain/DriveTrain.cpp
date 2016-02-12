#include <DriveTrain/DriveTrain.hpp>

void DriveTrain::Update(bool teleop)
{
	switch (state)
	{
		case (ANGLE_PID):
			anglePID->Enable();
			// anglePIDSource->SetPIDTarget(target);
			anglePID->SetSetpoint(0);

			output = anglePIDOutput->GetOutput();

			leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
			rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

			if (OnTargetAngle())
			{
				ChangeState(NO_STATE);
			}
			break;
		case (DRIVE_ENC):
			leftSpeedCurrent = leftDrive->GetSpeed();
			rightSpeedCurrent = rightDrive->GetSpeed();

			if (OnTargetDistance())
			{
				ChangeState(NO_STATE);
			}

			break;
		case (SHOOTER_TELOPERATION):
			target = (vision->GetGoalCenterX() / WEBCAM_PIXEL_WIDTH) * 2 - 1;
			anglePID->Enable();
			anglePIDSource->SetPIDTarget(target);
			anglePID->SetSetpoint(0);

			output = anglePIDOutput->GetOutput();

			leftSpeedCurrent = (output > 0) ? fabs(output) : -fabs(output);
			rightSpeedCurrent = (output > 0) ? -fabs(output) : fabs(output);

			if (OnTargetAngle())
			{
				ChangeState(CONTROL_TELOPERATION);
			}

			break;
		case (CONTROL_TELOPERATION):
			leftSpeedCurrent = joystick->GetRawAxis(DRIVE_AXIS_LEFT);
			rightSpeedCurrent = joystick->GetRawAxis(DRIVE_AXIS_RIGHT);
			break;
		case (NO_STATE):
			if (teleop)
			{
				state = CONTROL_TELOPERATION;
			}

			break;
	}

	// Deadband
	if (fabs(leftSpeedCurrent) < JOYSTICK_DEADBAND)
	{
		leftSpeedCurrent = 0;
	}

	if (fabs(rightSpeedCurrent) < JOYSTICK_DEADBAND)
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

	// Set the talons.
	leftDrive->Set(leftSpeedCurrent);
	rightDrive->Set(-rightSpeedCurrent);
}

void DriveTrain::Dashboard()
{
	SmartDashboard::PutNumber("Drive Speed Left", leftSpeedCurrent);
	SmartDashboard::PutNumber("Drive Speed Right", rightSpeedCurrent);

	SmartDashboard::PutNumber("Drive PID Angle Target", anglePIDSource->PIDGet());
	SmartDashboard::PutBoolean("Drive PID Angle On Target", anglePID->OnTarget());
}

void DriveTrain::ChangeState(int newState)
{
	state = newState;

	switch(state)
	{
		case(SHOOTER_TELOPERATION):
		case(ANGLE_PID):
			anglePID->Enable();
			leftDrive->SetControlMode(CANTalon::ControlMode::kPosition);
			rightDrive->SetControlMode(CANTalon::ControlMode::kPosition);
			break;
		case(DRIVE_ENC):
			anglePID->Disable();
			leftDrive->SetControlMode(CANTalon::ControlMode::kSpeed);
			rightDrive->SetControlMode(CANTalon::ControlMode::kSpeed);
			break;
		case(CONTROL_TELOPERATION):
			anglePID->Disable();
			leftDrive->SetControlMode(CANTalon::ControlMode::kPosition);
			rightDrive->SetControlMode(CANTalon::ControlMode::kPosition);
			break;
		case(NO_STATE):
			break;
	}
}

int DriveTrain::GetState()
{
	return state;
}

void DriveTrain::AutoDrive(float distanceFt)
{
	ChangeState(DRIVE_ENC);
	encoderGoal = distanceFt * DRIVE_FT_TO_ENCODER;

	leftDrive->Reset();
	rightDrive->Reset();

	leftDrive->Set(encoderGoal);
	rightDrive->Set(encoderGoal);
}

void DriveTrain::AutoAngle(float targetAngle)
{
	ChangeState(ANGLE_PID);
	double target = ((angleGyro->GetAngle() - targetAngle) * (1.0f / 360.0f)) * 2 - 1; // TODO: Check!
	anglePIDSource->SetPIDTarget(target);
}

bool DriveTrain::Waiting()
{
	return state == NO_STATE;
}

bool DriveTrain::OnTargetAngle()
{
	return anglePID->IsEnabled() && anglePID->OnTarget();
}

bool DriveTrain::OnTargetDistance()
{
	return (fabs(leftDrive->GetEncPosition() - encoderGoal) < DRIVE_DISTANCE_ERROR) && (fabs(rightDrive->GetEncPosition() - encoderGoal) < DRIVE_DISTANCE_ERROR);
}
