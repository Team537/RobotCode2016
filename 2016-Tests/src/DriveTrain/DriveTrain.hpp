#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include "Schematic.hpp"

class DriveTrain {
private:
	Victor *leftVictor;
	Victor *rightVictor;
	Solenoid *shifter;
	bool userControl;

public:
	DriveTrain() {
		leftVictor = new Victor(0);
		rightVictor = new Victor(1);
		shifter = new Solenoid(0);
		userControl = false;
	}

	void Update(Joystick * joystick);
	void Shift(int gear);
	void Drive(double leftSpeed, double rightSpeed);

	bool IsUserControl();
	void SetUserControl(bool userControl);
};

#endif
