#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP
#include "Schematic.hpp"
#include "Shooter/Shooter.hpp"

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

	void SetPIDCenter(double center)
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
	Victor *rightDrive;
	Victor *leftDrive;
	Solenoid *shifter;
	AnalogGyro *angleGyro;
	PIDController *visionPID;
	PIDController *robotAngle;
	VisionSource *visionSource;
	VisionOutput *visionOutput;
	Shooter *shooter;
	Joystick *joystick;
public:
	DriveTrain(Joystick *joystick)
	{
		rightDrive = new Victor(5);
		leftDrive = new Victor(6);
		shifter = new Solenoid(0);
		angleGyro= new AnalogGyro(0);
		visionSource = new VisionSource();
		visionOutput = new VisionOutput();
		visionPID = new PIDController(1, 0, 0, visionSource, visionOutput);
		robotAngle = new PIDController(1,0,0, angleGyro, rightDrive);
		joystick = joystick;
		shooter = new Shooter();


		leftSpeedCurrent = 0;
		rightSpeedCurrent = 0;
		leftSpeedOld = 0;
		rightSpeedOld = 0;
		leftSpeedDelta = 0;
		rightSpeedDelta = 0;
		leftDriveSign = 1;
		rightDriveSign = 1;
	}
	float leftSpeedCurrent;
	float rightSpeedCurrent;
	float leftSpeedOld;
	float rightSpeedOld;
	float leftSpeedDelta;
	float rightSpeedDelta;
	float leftDriveSign;
	float rightDriveSign;


	void Drive ();
	void TargetAngle(float TargetAngle);
	void FirePiston(bool FireOn, bool FireOff);
	void Shoot(bool ShooterOn);
};

#endif

