#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousReach: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Collector *collector;
        int reachState;
    public:
        AutonomousReach(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Collector *collector) :
                IAutonomous(chooser, defaultChooser, "Reach"),
                driveTrain(driveTrain),
                collector(collector),
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
