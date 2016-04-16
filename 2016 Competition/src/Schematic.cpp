#include <Schematic.hpp>

Joystick* Schematic::joystickPrimary = nullptr;
Joystick* Schematic::secondaryPrimary = nullptr;
Joystick* Schematic::secondaryTertiary = nullptr;
AHRS* Schematic::gryo = nullptr;

void Schematic::Init(Joystick* primary, Joystick* secondary, Joystick* tertiary, AHRS* ahrs)
{
    joystickPrimary = primary;
    secondaryPrimary = secondary;
    secondaryTertiary = tertiary;
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

Joystick* Schematic::GetTertiary()
{
    return secondaryTertiary;
}

AHRS* Schematic::GetGyro()
{
    return gryo;
}
