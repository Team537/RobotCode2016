#include "DriveTrain/DriveTrain.hpp"

void DriveTrain::Update(Joystick* joystick) {
	float leftJoy = fabs(joystick->GetRawAxis(0)) >= JOYSTICK_DEADBAND ? joystick->GetRawAxis(0) : 0;
	float rightJoy = fabs(joystick->GetRawAxis(2)) >= JOYSTICK_DEADBAND ? joystick->GetRawAxis(2) : 0;
	Drive(leftJoy, rightJoy);

	if(joystick->GetRawButton(5)){
		Shift(1);
	} else if(joystick->GetRawButton(7)){
		Shift(0);
	}
}

void DriveTrain::Drive(double leftSpeed, double rightSpeed){
	rightVictor->Set(rightSpeed);
	leftVictor->Set(leftSpeed);
}

void DriveTrain::Shift(int gear) {
	shifter->Set(gear == 1 ? false : true);
}

bool DriveTrain::IsUserControl() {
	return userControl;
}

void DriveTrain::SetUserControl(bool userControl) {
	this->userControl = userControl;
}
