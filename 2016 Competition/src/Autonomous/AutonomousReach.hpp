#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousReach: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        int reachState;
        Collector *collector;
    public:
        AutonomousReach(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "Reach"),
                driveTrain(driveTrain),
                reachState(0)
        {
        }

        virtual ~AutonomousReach()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
