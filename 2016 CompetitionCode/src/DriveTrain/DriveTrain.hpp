#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include <Schematic.hpp>
#include <Shooter/ShooterManager.hpp>
#include <Vision/VisionManager.hpp>

class VisionSource : public PIDSource
{
private:
	double center;
public:
	VisionSource()
	{
		center = -1;
	}

	void SetPIDSourceType(PIDSourceType pidSource)
	{
		m_pidSource = pidSource;
	}

	void SetPIDCenter(double center)
	{
		this->center = center;
	}

	double PIDGet()
	{
		return center;
	}
};

class VisionOutput : public PIDOutput
{
private:
	float output;
public:
	VisionOutput()
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

class DriveTrain : public IComponent
{
private:
	CANTalon *rightDrive;
	CANTalon *leftDrive;
	Solenoid *shifter;
	AnalogGyro *angleGyro;
	VisionSource *visionSource;
	VisionOutput *visionOutput;
	PIDController *visionPID;
	PIDController *robotAngle;
	ShooterManager *shooterManager;

	float currentSpeedLeft;
	float currentSpeedRight;
	float oldSpeedLeft;
	float oldSpeedRight;
	float deltaSpeedLeft;
	float deltaSpeedRight;
	float leftSign;
	float rightSign;
public:
	DriveTrain(Joystick *joystick, ShooterManager *shooterManager) : IComponent(joystick, new string("DriveTrain"))
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
		angleGyro= new AnalogGyro(0);
		visionSource = new VisionSource();
		visionOutput = new VisionOutput();
		visionPID = new PIDController(1, 0, 0, visionSource, visionOutput);
		robotAngle = new PIDController(1, 0, 0, angleGyro, rightDrive);
		this->shooterManager = shooterManager;

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

	void AutoAngle(float targetAngle);
};

#endif

