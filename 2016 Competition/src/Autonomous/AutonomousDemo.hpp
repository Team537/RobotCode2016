#pragma once

#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousDemo: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        int reachState;

    public:
        AutonomousDemo(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "Demo"),
                driveTrain(driveTrain),
                reachState(0)
        {
        }

        virtual ~AutonomousDemo()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
