#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include "Schematic.hpp"
#include "Robot.cpp"

class IComponent {
private:
	Joystick *joystick;
	Robot *robot;
	std::string *name;
public:
	IComponent(Joystick *joystick, Robot *robot, std::string *name) {
		this->joystick = joystick;
		this->robot = robot;
		this->name = name;
	}

	virtual ~IComponent();

	virtual void Update() {}
	virtual void Dashboard() {}
	virtual void CleanUp() {}

	std::string* GetName() {
		return name;
	}
};

#endif
