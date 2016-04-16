#pragma once

#include <Schematic.hpp>

using namespace std;

class IAutonomous
{
    private:
        string name;

    public:
        IAutonomous(SendableChooser *chooser, bool defaultChooser, string autoName)
        {
            name = autoName;

            if (defaultChooser)
            {
                chooser->AddDefault(name, this);
            }
            else
            {
                chooser->AddObject(name, this);
            }
        }

        virtual ~IAutonomous()
        {
        }

        virtual void Start()
        {
        }

        virtual bool Run(const double& time)
        {
            return false;
        }

        virtual void Stop()
        {
        }

        inline string GetName() const { return name; }
};
