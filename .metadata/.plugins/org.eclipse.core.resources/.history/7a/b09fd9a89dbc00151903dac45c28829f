#ifndef SWERVE_HPP
#define SWERVE_HPP

#include "Schematic.hpp"
#include "MyButton.hpp"
#include "SwerveModule.hpp"

class Swerve {
private:
	Joystick *joystick;
	Gyro* gyro;
	MyButton *tuningButton;
	SwerveModule *frontRight, *frontLeft, *backLeft, *backRight;

public:
	Swerve(Joystick *joystick, Gyro *gyro) {
		this->joystick = joystick;
		this->gyro = gyro;
		this->tuningButton = new MyButton(joystick, 10);

		frontLeft = new SwerveModule("Front Right", 9, 6);
		frontRight = new SwerveModule("Front Left", 8, 3);
		backRight = new SwerveModule("Back Left", 4, 1);
		backLeft = new SwerveModule("Back Right", 5, 2);
	}

	void Drive();
	void Tune(SwerveModule *module);
	void Dashboard();
};

#endif
