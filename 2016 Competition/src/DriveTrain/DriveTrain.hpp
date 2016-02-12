#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include <Schematic.hpp>
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

	VisionManager *vision;

	DrivePIDSource *anglePIDSource;
	DrivePIDOutput *anglePIDOutput;
	PIDController *anglePID;

	int state;
	float encoderGoal;

	float leftSpeedCurrent;
	float rightSpeedCurrent;
	float leftSpeedOld;
	float rightSpeedOld;
	float leftSpeedDelta;
	float rightSpeedDelta;
	float leftDriveSign;
	float rightDriveSign;
public:
	DriveTrain(Joystick *joystick, AnalogGyro *gyro, VisionManager *vision) : IComponent(joystick, new string("DriveTrain"))
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
		this->vision = vision;

		anglePIDSource = new DrivePIDSource();
		anglePIDOutput = new DrivePIDOutput();
		anglePID = new PIDController(1, 0, 0, anglePIDSource, anglePIDOutput);
		anglePID->SetAbsoluteTolerance(0.05);
		anglePID->Disable();

		state = CONTROL_TELOPERATION;
		encoderGoal = 0;

		leftSpeedCurrent = 0;
		rightSpeedCurrent = 0;
		leftSpeedOld = 0;
		rightSpeedOld = 0;
		leftSpeedDelta = 0;
		rightSpeedDelta = 0;
		leftDriveSign = 1;
		rightDriveSign = 1;
		target = 0;
		output = 0;
	}

	void Update(bool teleop);
	void Dashboard();
	void ChangeState(int newState);
	int GetState();

	void AutoDrive(float distanceFt);
	void AutoAngle(float targetAngle);
	bool Waiting();
	bool OnTargetAngle();
	bool OnTargetDistance();
	double output;
	double target;
};

#endif

