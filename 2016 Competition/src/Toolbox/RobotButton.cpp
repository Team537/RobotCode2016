#include <Toolbox/RobotButton.hpp>

bool RobotButton::GetState()
{
    return joystick->GetRawButton(key);
}

bool RobotButton::WasDown()
{
    bool stillDown = lastState && GetState();
    lastState = GetState();
    return lastState == !stillDown;
}
