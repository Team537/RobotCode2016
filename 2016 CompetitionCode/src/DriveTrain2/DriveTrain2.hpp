#ifndef DRIVETRAIN2_HPP
#define DRIVETRAIN2_HPP

#include <DriveTrain2/DrivePID.hpp>
#include <Schematic.hpp>
#include <Shooter/ShooterManager.hpp>
#include <Vision/VisionManager.hpp>

class DriveTrain2 : IComponent {
private:
	CANTalon *leftDrive, *rightDrive;
	Encoder *leftEncoder, *rightEncoder;
	AnalogGyro *analogGyro;
	ShooterManager *shooterManager;

	Victor *outputAngle, *outputSpeed;
	PIDController *anglePID, *distancePID;

	float leftSpeed, rightSpeed;

	float targetAngle, targetDistance;

public:
	DriveTrain2(Joystick *joystick, AnalogGyro *gyro, ShooterManager *shooter) : IComponent(joystick, new string("DriveTrain2"))
	{
		rightDrive = new CANTalon(0);
		rightDrive->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		rightDrive->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		rightDrive->SetControlMode(CANTalon::ControlMode::kSpeed);
		rightDrive->EnableControl();

		leftDrive = new CANTalon(1);
		leftDrive->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		leftDrive->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		leftDrive->SetControlMode(CANTalon::ControlMode::kSpeed);
		leftDrive->EnableControl();

		leftEncoder = new Encoder(0);
		rightEncoder = new Encoder(1);

		analogGyro = gyro;
		shooterManager = shooter;

		anglePID = new PIDController(0.777, 0, 0, analogGyro, outputAngle);
		anglePID->SetInputRange(AnglePIDValues->MINInput, AnglePIDValues->MAXInput);
		anglePID->SetOutputRange(AnglePIDValues->MINOutput, AnglePIDValues->MaxOutput);
		anglePID->SetAbsoluteTolerance(20);

		distancePID = new PIDController(0.777, 0, 0, encoderSpeed, distancePIDOutput);
		distancePID->SetAbsoluteTolerance(0.05);
		distancePID->SetInputRange(-1, 1);
		distancePID->SetOutputRange(-1, 1);
		distancePID->Disable();

		leftSpeed = 0;
		rightSpeed = 0;

		targetAngle = 0;
		targetDistance = 0;
	}

	void Update(bool teleop);
	void Dashboard();

	void AutoAngle(float angle);
	void AutoDistance(float distance);
	bool AtTargetAngle();
	bool AtTargetDistance();
};

#endif
