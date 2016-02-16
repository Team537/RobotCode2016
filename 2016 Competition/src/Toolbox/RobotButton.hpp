#ifndef ROBOTBUTTON_HPP
#define ROBOTBUTTON_HPP

#include <Schematic.hpp>

class RobotButton
{
    private:
        Joystick *joystick;
        unsigned int key;bool lastState;

    public:
        RobotButton(Joystick *joystick, unsigned int key)
        {
            this->joystick = joystick;
            this->key = key;
            this->lastState = false;
        }

        bool GetState();bool WasDown();
};

#endif
