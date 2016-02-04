#include <DriveTrain/DriveTrain.hpp>

void DriveTrain::Update(bool teleop)
{

	if (shooterManager->IsActivated())
	{
		double target = (shooterManager->GetVision()->GetGoalCenterX() / WEBCAM_PIXEL_WIDTH) * 2 - 1;

		anglePID->Enable();
		anglePIDSource->SetPIDTarget(target);
		anglePID->SetSetpoint(0);

		double output = anglePIDOutput->GetOutput();

		currentSpeedLeft = (output > 0) ? fabs(output) : -fabs(output);
		currentSpeedRight = (output > 0) ? -fabs(output) : fabs(output);

		if (anglePID->OnTarget())
		{
			anglePID->Disable();
		}
	}
	else
	{
		DisablePIDs();
		currentSpeedLeft = joystick->GetRawAxis(DRIVE_AXIS_LEFT);
		currentSpeedRight = joystick->GetRawAxis(DRIVE_AXIS_RIGHT);
	}

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

void DriveTrain::Dashboard()
{
	SmartDashboard::PutNumber("Drive Speed Left", currentSpeedLeft);
	SmartDashboard::PutNumber("Drive Speed Right", currentSpeedRight);

	SmartDashboard::PutNumber("Drive PID Angle Target", anglePIDSource->PIDGet());
	SmartDashboard::PutBoolean("Drive PID Angle On Target", anglePID->OnTarget());

	SmartDashboard::PutNumber("Drive PID Distance Target", drivePID->Get());
	SmartDashboard::PutBoolean("Drive PID Distance On Target", drivePID->OnTarget());
}

void DriveTrain::DisablePIDs()
{
	anglePID->Disable();
	drivePID->Disable();
}


void DriveTrain::AutonomousInit()
{
	leftDrive->SetControlMode(CANTalon::ControlMode::kPosition);
	rightDrive->SetControlMode(CANTalon::ControlMode::kPosition);
}

void DriveTrain::TeleOpInit()
{
	leftDrive->SetControlMode(CANTalon::ControlMode::kSpeed);
	rightDrive->SetControlMode(CANTalon::ControlMode::kSpeed);
}

void DriveTrain::AutoDrive(float distanceFt)
{

	double target = distanceFt;
	drivePID->SetSetpoint(target);
}


bool DriveTrain::AutoAngle(float targetAngle)
{
	anglePID->Enable();
	double target = ((angleGyro->GetAngle() - targetAngle) * (1.0f / 360.0f)) * 2 - 1; // TODO: Double check this!
	anglePIDSource->SetPIDTarget(target);
	return anglePID->OnTarget();
}

