#ifndef CLIMBER_HPP
#define CLIMBER_HPP

#include <Schematic.hpp>
#include <Toolbox/RobotButton.hpp>

class Climber: public IComponent
{
private:
	DigitalInput *leftRetracted, *rightRetracted, *leftExtended, *rightExtended;
	Solenoid *leftHook, *rightHook, *backLeftExtender, *frontLeftExtender, *backRightExtender, *frontRightExtender;
	RobotButton *extenderButton, *hookButton;

public:
	Climber(Joystick* joystick) : IComponent(joystick, new string("Climber"))
	{
		extenderButton = new RobotButton(joystick, 0),
		hookButton = new RobotButton(joystick, 0),
		leftRetracted = new DigitalInput(0),
		rightRetracted = new DigitalInput(0),
		leftExtended = new DigitalInput(0),
		rightExtended = new DigitalInput(0),
		leftHook = new Solenoid(0),
		rightHook = new Solenoid(0),
		backLeftExtender = new Solenoid(0),
		frontLeftExtender = new Solenoid(0),
		backRightExtender = new Solenoid(0),
		frontRightExtender = new Solenoid(0);
	}

	void Update(bool teleop);
	void Dashboard();

	void Reset();
	void Extend();
	void Hook();

	bool IsExtended();
	bool IsHooked();
};

#endif
