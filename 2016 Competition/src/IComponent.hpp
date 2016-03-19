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

        virtual ~IComponent()
        {
        }

        void ComponentUpdate(const double& teleop)
        {
            Update(teleop);
            Dashboard();
        }

        virtual void Update(const double& teleop)
        {
        }

        virtual void Dashboard()
        {
        }

        inline string* GetName() const { return name; }
};

#endif
