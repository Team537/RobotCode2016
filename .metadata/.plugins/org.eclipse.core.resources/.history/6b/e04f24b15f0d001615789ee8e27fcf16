#pragma once

#include <Schematic.hpp>

class AutonomousNone: public IAutonomous
{
    private:

    public:
        AutonomousNone(SendableChooser *chooser, bool defaultChooser) :
                IAutonomous(chooser, defaultChooser, "None")
        {
        }

        virtual ~AutonomousNone()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
