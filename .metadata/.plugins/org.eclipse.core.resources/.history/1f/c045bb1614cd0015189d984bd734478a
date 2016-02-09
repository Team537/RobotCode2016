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
		leftSpeedCurrent = visionOutput->GetOutput();
		SmartDashboard::PutNumber("Right Drive", visionOutput->GetOutput());

	}
	else{
		// get the position of the left and right joysticks
		leftSpeedCurrent = joystick->GetRawAxis(LEFT_AXIS);
		rightSpeedCurrent = joystick->GetRawAxis(RIGHT_AXIS);
		// deadband
		if (fabs(leftSpeedCurrent) < JOYSTICK_DEADBAND)
		{
			leftSpeedCurrent = 0;
		}
		if (fabs(rightSpeedCurrent) < JOYSTICK_DEADBAND)
		{
			rightSpeedCurrent = 0;
		}
		// ramping
		leftSpeedDelta = leftSpeedCurrent - leftSpeedOld;
		leftSpeedDelta = rightSpeedCurrent - rightSpeedOld;
		leftDriveSign = leftSpeedCurrent/fabs(leftSpeedCurrent);
		rightDriveSign = rightSpeedCurrent/fabs(rightSpeedCurrent);
		if (fabs(leftSpeedDelta) > RAMP_SPEED)
		{
			leftSpeedCurrent = leftSpeedOld + leftDriveSign*RAMP_SPEED;
		}
		if (fabs(rightSpeedDelta) > RAMP_SPEED)
		{
			rightSpeedCurrent = rightSpeedOld + rightDriveSign*RAMP_SPEED;
		}
		// clamping
		if (fabs(leftSpeedCurrent) > 1)
		{
			leftSpeedCurrent = leftDriveSign;
		}
		if (fabs(rightSpeedCurrent) > 1)
		{
			rightSpeedCurrent = rightDriveSign;
		}
		// log the left and right speeds
		leftSpeedOld = leftSpeedCurrent;
		rightSpeedOld = rightSpeedCurrent;
		// set the motors
		leftDrive->SetSpeed(leftSpeedCurrent);
		rightDrive->SetSpeed(-rightSpeedCurrent);
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
