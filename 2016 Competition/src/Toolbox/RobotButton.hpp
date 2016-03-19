#pragma once

#include <Schematic.hpp>

class RobotButton
{
    private:
        Joystick *joystick;
        unsigned int key;
        bool axis;
        bool lastState;

    public:
        RobotButton(Joystick *joystick, unsigned int key, bool axis) :
            joystick(joystick),
            key(key),
            axis(axis),
            lastState(false)
        {
        }

        virtual ~RobotButton()
        {
        }

        bool GetState();
        bool WasDown();
};
