#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <Schematic.hpp>

using namespace std;

class IComponent
{
    private:
        string* name;

    public:
        Joystick* joystickPrimary;
        Joystick* joystickSecondary;

        IComponent(Joystick* joystickPrimary, Joystick* joystickSecondary, string* name)
        {
            this->joystickPrimary = joystickPrimary;
            this->joystickSecondary = joystickSecondary;
            this->name = name;
        }

        void ComponentUpdate(bool teleop)
        {
            Update(teleop);
            Dashboard();
        }

        virtual void Update(bool teleop)
        {
        }

        virtual void Dashboard()
        {
        }

        inline string* GetName()
        {
            return name;
        }
};

#endif
