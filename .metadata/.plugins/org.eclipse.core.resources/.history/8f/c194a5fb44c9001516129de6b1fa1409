#ifndef MYBUTTON_HPP
#define MYBUTTON_HPP

#include "WPILib.h"

class MyButton {
private:
	Joystick *joystick;
	unsigned int key;
	bool lastState;

public:
	MyButton(Joystick *joystick, unsigned int key) {
		this->joystick = joystick;
		this->key = key;
		this->lastState = false;
	}

	bool GetState();
	bool WasDown();
};

#endif
