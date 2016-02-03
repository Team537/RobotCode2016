#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include <Schematic.hpp>
#include <Shooter/ShooterManager.hpp>
#include <Vision/VisionManager.hpp>

class DrivePIDSource: public PIDSource
{
private:
	double target;
public:
	DrivePIDSource()
	{
		target = -1;
	}

	void SetPIDSourceType(PIDSourceType pidSource)
	{
		m_pidSource = pidSource;
	}

	void SetPIDTarget(double center)
	{
		this->target = center;
	}

	double PIDGet()
	{
		return target;
	}
};

class DrivePIDOutput: public PIDOutput
{
private:
	float output;
public:
	DrivePIDOutput()
	{
		output = 0;
	}

	void PIDWrite(float output)
	{
		this->output = output;
	}

	float GetOutput()
	{
		return output;
	}
};

class DriveTrain: public IComponent
{
private:
	CANTalon *rightDrive;
	CANTalon *leftDrive;
	Solenoid *shifter;
	AnalogGyro *angleGyro;
	ShooterManager *shooterManager;

	DrivePIDSource *drivePIDSource;
	DrivePIDOutput *drivePIDOutput;
	PIDController *drivePID;

	float currentSpeedLeft;
	float currentSpeedRight;
	float oldSpeedLeft;
	float oldSpeedRight;
	float deltaSpeedLeft;
	float deltaSpeedRight;
	float leftSign;
	float rightSign;
public:
	DriveTrain(Joystick *joystick, AnalogGyro *gyro, ShooterManager *shooter) : IComponent(joystick, new string("DriveTrain"))
	{
		rightDrive = new CANTalon(5);
		rightDrive->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		rightDrive->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		rightDrive->EnableControl();

		leftDrive = new CANTalon(6);
		leftDrive->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		leftDrive->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		leftDrive->EnableControl();

		shifter = new Solenoid(0);
		angleGyro = gyro;
		shooterManager = shooter;

		drivePIDSource = new DrivePIDSource();
		drivePIDOutput = new DrivePIDOutput();
		drivePID = new PIDController(1, 0, 0, drivePIDSource, drivePIDOutput);

		currentSpeedLeft = 0;
		currentSpeedRight = 0;
		oldSpeedLeft = 0;
		oldSpeedRight = 0;
		deltaSpeedLeft = 0;
		deltaSpeedRight = 0;
		leftSign = 1;
		rightSign = 1;
	}

	void Update();
	void Dashboard();

	bool AutoAngle(float targetAngle);
};

#endif

