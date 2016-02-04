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

	DrivePIDSource *anglePIDSource;
	DrivePIDOutput *anglePIDOutput;
	PIDController *anglePID;

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
		rightDrive->SetControlMode(CANTalon::ControlMode::kSpeed);
		rightDrive->EnableControl();

		leftDrive = new CANTalon(6);
		leftDrive->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		leftDrive->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		leftDrive->EnableControl();

		shifter = new Solenoid(0);
		angleGyro = gyro;
		shooterManager = shooter;

		anglePIDSource = new DrivePIDSource();
		anglePIDOutput = new DrivePIDOutput();
		anglePID = new PIDController(1, 0, 0, anglePIDSource, anglePIDOutput);
		anglePID->SetAbsoluteTolerance(0.05);
		anglePID->Disable();

		drivePID = new PIDController(1, 0, 0, angleGyro, rightDrive);
		drivePID->Disable();

		currentSpeedLeft = 0;
		currentSpeedRight = 0;
		oldSpeedLeft = 0;
		oldSpeedRight = 0;
		deltaSpeedLeft = 0;
		deltaSpeedRight = 0;
		leftSign = 1;
		rightSign = 1;
	}

	void Update(bool teleop);
	void AutonomousInit();
	void TeleOpInit();
	void Dashboard();
	bool OnTarget();

	void DisablePIDs();

	void AutoDrive(float distanceFt);
	void AutoAngle(float targetAngle);
};

#endif

