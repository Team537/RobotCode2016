#include <Toolbox/RobotButton.hpp>

float RobotButton::GetAxis()
{
    if (controlsType != AXIS)
    {
    //    char* error = "Getting values for axis " + key + " failed because it is not an axis type!";
    //    DriverStation::ReportError(error);
    //    delete[] error;
    }

    return (joystickType == PRIMARY ? Schematic::GetPrimary() : Schematic::GetSecondary())->GetRawAxis(key);
}

bool RobotButton::GetKey()
{
    if (controlsType != KEY)
    {
    //    char* error = "Getting values for key " + key + " failed because it is not a key type!";
    //    DriverStation::ReportError(error);
    //    delete[] error;
    }

    return (joystickType == PRIMARY ? Schematic::GetPrimary() : Schematic::GetSecondary())->GetRawButton(key);
}

bool RobotButton::WasDown()
{
    bool stillDown = lastState && GetKey();
    lastState = GetKey();
    return lastState == !stillDown;
}
