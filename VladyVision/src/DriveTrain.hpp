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


		currentSpeedLeft = 0;
		currentSpeedRight = 0;
		oldSpeedLeft = 0;
		oldSpeedRight = 0;
		deltaSpeedLeft = 0;
		deltaSpeedRight = 0;
		leftSign = 1;
		rightSign = 1;
	}
	float currentSpeedLeft;
	float currentSpeedRight;
	float oldSpeedLeft;
	float oldSpeedRight;
	float deltaSpeedLeft;
	float deltaSpeedRight;
	float leftSign;
	float rightSign;


	void Drive ();
	void AutoAngle(float TargetAngle);
	void FirePiston(bool FireOn, bool FireOff);
	void Shoot(bool ShooterOn);
};

#endif

