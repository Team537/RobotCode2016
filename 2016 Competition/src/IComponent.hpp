#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <Schematic.hpp>

using namespace std;

class IComponent
{
    private:
        string* name;

    public:
        Joystick* joystick;

        IComponent(Joystick* joystick, string* name)
        {
            this->joystick = joystick;
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
