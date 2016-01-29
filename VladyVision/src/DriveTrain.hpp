#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP
#include "Schematic.hpp"

class VisionSource: public PIDSource
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

	void PIDCenter(double center)
	{
		this->center = center;
	}

	double PIDGet()
	{
		return center;
	}
};

class VisionOutput: public PIDOutput
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

class DriveTrain
{
private:
	Victor *RightDrive;
	Victor *LeftDrive;
	Solenoid *Shifter;
	Gyro *AngleGyro;
	PIDController *VisionPID;
	PIDController *RobotAngle;
	VisionSource *visionSource;
	VisionOutput *visionOutput;
public:
	DriveTrain()
	{
		RightDrive = new Victor(0);
		LeftDrive = new Victor(1);
		Shifter = new Solenoid(0);
		AngleGyro= new Gyro(0);
		visionSource = new VisionSource();
		visionOutput = new VisionOutput();
		VisionPID = new PIDController(1, 0, 0, visionSource, visionOutput);
		RobotAngle = new PIDController(1,0,0, AngleGyro, RightDrive);

		CurrentSpeedLeft = 0;
		CurrentSpeedRight = 0;
		OldSpeedLeft = 0;
		OldSpeedRight = 0;
		DeltaSpeedLeft = 0;
		DeltaSpeedRight = 0;
		LeftSign = 1;
		RightSign = 1;
	}
	float CurrentSpeedLeft;
	float CurrentSpeedRight;
	float OldSpeedLeft;
	float OldSpeedRight;
	float DeltaSpeedLeft;
	float DeltaSpeedRight;
	float LeftSign;
	float RightSign;

	void Drive (Joystick *Joy);
	void AutoAngle(float TargetAngle);
};

#endif

