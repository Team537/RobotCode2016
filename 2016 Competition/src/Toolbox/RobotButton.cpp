#include <Toolbox/RobotButton.hpp>

bool RobotButton::GetState()
{
    if (axis)
    {
        return joystick->GetRawAxis(key) > CONTROLLER_DEADBAND;
    }
    else
    {
        return joystick->GetRawButton(key);
    }
}

bool RobotButton::WasDown()
{
    bool stillDown = lastState && GetState();
    lastState = GetState();
    return lastState == !stillDown;
}
