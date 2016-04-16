#pragma once

#include <Schematic.hpp>

class RobotButton
{
    public:
        enum JoystickType { PRIMARY, SECONDARY, TERTIARY };
        enum ControlTypes { KEY, AXIS };

        RobotButton(JoystickType joystickType, ControlTypes controlsType, unsigned int key) :
            joystickType(joystickType),
            controlsType(controlsType),
            key(key),
            lastState(false)
        {
        }

        virtual ~RobotButton()
        {
        }

        float GetAxis();
        bool GetKey();
        bool WasDown();
    private:
        JoystickType joystickType;
        ControlTypes controlsType;
        unsigned int key;
        bool lastState;
};
