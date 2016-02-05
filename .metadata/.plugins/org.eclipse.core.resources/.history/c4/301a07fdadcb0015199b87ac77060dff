// include header files
#include <DriveTrain.hpp>

// function that sets the speed of the motors
void DriveTrain::Drive ()
{
	if (shooter->isActivated()) {
		double goalPosX = (shooter->GetVision()->GetGoalXOffset() / WEBCAM_PIXEL_WIDTH) * 2 - 1;
		visionPID->Enable();
		visionSource->SetPIDCenter(goalPosX);
		visionPID->SetSetpoint(0);
		currentSpeedLeft = visionOutput->GetOutput();
		SmartDashboard::PutNumber("Right Drive", visionOutput->GetOutput());

	}
	else{
		// get the position of the left and right joysticks
		currentSpeedLeft = joystick->GetRawAxis(LEFT_AXIS);
		currentSpeedRight = joystick->GetRawAxis(RIGHT_AXIS);
		// deadband
		if (fabs(currentSpeedLeft) < JOYSTICK_DEADBAND)
		{
			currentSpeedLeft = 0;
		}
		if (fabs(currentSpeedRight) < JOYSTICK_DEADBAND)
		{
			currentSpeedRight = 0;
		}
		// ramping
		deltaSpeedLeft = currentSpeedLeft - oldSpeedLeft;
		deltaSpeedLeft = currentSpeedRight - oldSpeedRight;
		leftSign = currentSpeedLeft/fabs(currentSpeedLeft);
		rightSign = currentSpeedRight/fabs(currentSpeedRight);
		if (fabs(deltaSpeedLeft) > RAMP_SPEED)
		{
			currentSpeedLeft = oldSpeedLeft + leftSign*RAMP_SPEED;
		}
		if (fabs(deltaSpeedRight) > RAMP_SPEED)
		{
			currentSpeedRight = oldSpeedRight + rightSign*RAMP_SPEED;
		}
		// clamping
		if (fabs(currentSpeedLeft) > 1)
		{
			currentSpeedLeft = leftSign;
		}
		if (fabs(currentSpeedRight) > 1)
		{
			currentSpeedRight = rightSign;
		}
		// log the left and right speeds
		oldSpeedLeft = currentSpeedLeft;
		oldSpeedRight = currentSpeedRight;
		// set the motors
		leftDrive->SetSpeed(currentSpeedLeft);
		rightDrive->SetSpeed(-currentSpeedRight);
	}
}

void DriveTrain::FirePiston(bool FireOn, bool FireOff)
{
	shooter->Feed(FireOn, FireOff);
}

void DriveTrain::Shoot(bool ShooterOn)
{
	shooter->Shoot(ShooterOn);
}
