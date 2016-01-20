#ifndef SWERVE_HPP
#define SWERVE_HPP

#include "Schematic.hpp"
#include "MyButton.hpp"
#include "SwerveModule.hpp"
#include "Shooter.hpp"

class VisionSource: public PIDSource {
private:
	double center;
public:
	VisionSource() {
		center = -1;
	}

	void SetPIDSourceType(PIDSourceType pidSource) {
		m_pidSource = pidSource;
	}

	void PIDCenter(double center) {
		this->center = center;
	}

	double PIDGet() {
		return center;
	}
};

class VisionOutput: public PIDOutput {
private:
	float output;
public:
	VisionOutput() {
		output = 0;
	}

	void PIDWrite(float output) {
		this->output = output;
	}

	float GetOutput() {
		return output;
	}
};

class Swerve {
private:
	Joystick *joystick;
	Gyro* gyro;
	MyButton *tuningButton;
	SwerveModule *frontRight, *frontLeft, *backLeft, *backRight;

	VisionSource *visionSource;
	VisionOutput *visionOutput;
	PIDController *visionPID;

public:
	Swerve(Joystick *joystick, Gyro *gyro) {
		this->joystick = joystick;
		this->gyro = gyro;
		this->tuningButton = new MyButton(joystick, 10);

		frontLeft = new SwerveModule("Front Right", 9, 6);
		frontRight = new SwerveModule("Front Left", 8, 3);
		backRight = new SwerveModule("Back Left", 4, 1);
		backLeft = new SwerveModule("Back Right", 5, 2);

		visionSource = new VisionSource();
		visionOutput = new VisionOutput();
		visionPID = new PIDController(0.01, 0, 0, visionSource, visionOutput);
		visionPID->SetAbsoluteTolerance(0.05);
		visionPID->SetInputRange(-1, 1);
		visionPID->SetOutputRange(-1, 1);
	}

	void Drive(Shooter *shooter);
	void Tune(SwerveModule *module);
	void Dashboard();
};

#endif
