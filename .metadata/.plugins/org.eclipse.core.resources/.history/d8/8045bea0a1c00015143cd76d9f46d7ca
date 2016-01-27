#ifndef SHOOTER_HPP
#define SHOOTER_HPP

#include "Schematic.hpp"
#include "Shooter/ShooterVision.hpp"
#include "Toolbox/MyButton.hpp"

class Shooter {
private:
	Joystick *joystick;
	ShooterVision *vision;
	MyButton *activateButton;
	bool activated;

public:
	Shooter(Joystick *joy) {
		joystick = joy;
		vision = new ShooterVision();
		activateButton = new MyButton(joystick, 10);
		activated = true;
	}

	void Update();
	void Dashboard();
	bool IsActivated();
	inline ShooterVision* GetVision() { return vision; }
};

#endif
