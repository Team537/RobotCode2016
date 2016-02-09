#include "MyButton.hpp"

bool MyButton::GetState()
{
	return joystick->GetRawButton(key);
}

bool MyButton::WasDown()
{
	bool stillDown = lastState && GetState();
	lastState = GetState();
	return lastState == !stillDown;
}
