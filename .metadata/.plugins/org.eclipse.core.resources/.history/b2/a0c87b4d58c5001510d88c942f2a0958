#include <DriveTrain.hpp>

void DriveTrain::run (Joystick *Joy){
	float leftJoy = fabs(Joy->GetRawAxis(0)) >= JOYSTICK_DEADBAND ? Joy->GetRawAxis(0) : 0;
	float rightJoy = fabs(Joy->GetRawAxis(2)) >= JOYSTICK_DEADBAND ? Joy->GetRawAxis(2) : 0;

	RightDrive->Set(leftJoy);
	LeftDrive->Set(rightJoy);

	if(Joy->GetRawButton(5)){
		Shifter->Set(true);
	} else if(Joy->GetRawButton(7)){
		Shifter->Set(false);
	}
}
