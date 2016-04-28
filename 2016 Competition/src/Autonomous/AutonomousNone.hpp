#pragma once

#include <Schematic.hpp>
#include <Climber/Climber.hpp>

class AutonomousNone: public IAutonomous
{
    private:
        Climber *climber;
    public:
        AutonomousNone(SendableChooser *chooser, bool defaultChooser, Climber* climber) :
                climber(climber),
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
