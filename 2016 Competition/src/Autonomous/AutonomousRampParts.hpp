#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousRampParts: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Collector *collector;
        int crossState;
    public:
        AutonomousRampParts(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Collector *collector) :
                IAutonomous(chooser, defaultChooser, "RampParts"),
                driveTrain(driveTrain),
                collector(collector),
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
