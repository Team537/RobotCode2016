#pragma once

#include <Schematic.hpp>

using namespace std;

class IComponent
{
    private:
        string* name;

    public:
        IComponent(string* name)
        {
            this->name = name;
        }

        virtual ~IComponent()
        {
        }

        void ComponentUpdate(const bool& teleop)
        {
            Update(teleop);
            Dashboard();
        }

        virtual void Update(const bool& teleop)
        {
        }

        virtual void Dashboard()
        {
        }

        inline string* GetName() const { return name; }
};
