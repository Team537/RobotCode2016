#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousRampParts: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        int crossState;
        Collector *collector;
    public:
        AutonomousRampParts(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "RampParts"),
                driveTrain(driveTrain),
                crossState(0)
        {
        }

        virtual ~AutonomousRampParts()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
