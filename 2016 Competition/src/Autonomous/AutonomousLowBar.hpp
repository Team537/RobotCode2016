#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousLowBar: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Collector *collector;
        Timer *autoTime;
        int crossState;

    public:
        AutonomousLowBar(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Collector *collector) :
                IAutonomous(chooser, defaultChooser, "LowBar"),
                driveTrain(driveTrain),
                collector(collector),
                autoTime(new Timer()),
                crossState(0)
        {
        }

        virtual ~AutonomousLowBar()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
