#include <DriveTrain/DriveTrain.hpp>

void DriveTrain::Update()
{
	if (shooterManager->IsActivated())
	{
		double goalPosX = (shooterManager->GetVision()->GetGoalCenterX() / WEBCAM_PIXEL_WIDTH) * 2 - 1;
		visionPID->Enable();
		visionSource->SetPIDCenter(goalPosX);
		visionPID->SetSetpoint(0);
		currentSpeedLeft = visionOutput->GetOutput();
	}
	else
	{
		// Get the position of the left and right joysticks.
		currentSpeedLeft = joystick->GetRawAxis(DRIVE_AXIS_LEFT);
		currentSpeedRight = joystick->GetRawAxis(DRIVE_AXIS_RIGHT);

		// Deadband.
		if (fabs(currentSpeedLeft) < JOYSTICK_DEADBAND)
		{
			currentSpeedLeft = 0;
		}

		if (fabs(currentSpeedRight) < JOYSTICK_DEADBAND)
		{
			currentSpeedRight = 0;
		}

		// Ramping.
		deltaSpeedLeft = currentSpeedLeft - oldSpeedLeft;
		deltaSpeedLeft = currentSpeedRight - oldSpeedRight;
		leftSign = currentSpeedLeft / fabs(currentSpeedLeft);
		rightSign = currentSpeedRight / fabs(currentSpeedRight);

		if (fabs(deltaSpeedLeft) > DRIVE_RAMP_SPEED)
		{
			currentSpeedLeft = oldSpeedLeft + leftSign * DRIVE_RAMP_SPEED;
		}

		if (fabs(deltaSpeedRight) > DRIVE_RAMP_SPEED)
		{
			currentSpeedRight = oldSpeedRight + rightSign * DRIVE_RAMP_SPEED;
		}

		// Clamping.
		if (fabs(currentSpeedLeft) > 1)
		{
			currentSpeedLeft = leftSign;
		}

		if (fabs(currentSpeedRight) > 1)
		{
			currentSpeedRight = rightSign;
		}

		// Log the left and right speeds.
		oldSpeedLeft = currentSpeedLeft;
		oldSpeedRight = currentSpeedRight;

		// Set the motors.
		leftDrive->Set(currentSpeedLeft);
		rightDrive->Set(-currentSpeedRight);
	}
}

void DriveTrain::Dashboard()
{
	SmartDashboard::PutNumber("Drive Speed Left", currentSpeedLeft);
	SmartDashboard::PutNumber("Drive Speed Right", currentSpeedRight);
}

void DriveTrain::AutoAngle(float targetAngle)
{
	// TODO!
}

