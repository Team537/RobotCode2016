#include <Schematic.hpp>

Joystick* Schematic::joystickPrimary = nullptr;
Joystick* Schematic::secondaryPrimary = nullptr;
AHRS* Schematic::gryo = nullptr;

void Schematic::Init(Joystick* primary, Joystick* secondary, AHRS* ahrs)
{
    joystickPrimary = primary;
    secondaryPrimary = secondary;
    gryo = ahrs;
}

Joystick* Schematic::GetPrimary()
{
    return joystickPrimary;
}

Joystick* Schematic::GetSecondary()
{
    return secondaryPrimary;
}

AHRS* Schematic::GetGyro()
{
    return gryo;
}
