#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <Schematic.hpp>

using namespace std;

class IComponent {
public:
	Joystick *joystick;
	string *name;

	IComponent(Joystick *joystick, string *name)
	{
		this->joystick = joystick;
		this->name = name;
	}

	void ComponentUpdate(bool teleop)
	{
		Update(teleop);
		Dashboard();
	}

	virtual void Update(bool teleop) {}
	virtual void Dashboard() {}
};

#endif
