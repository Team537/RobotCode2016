#pragma once

#include <DriveTrain/DriveTrain.hpp>
#include <Collector/Collector.hpp>
#include <Schematic.hpp>

class AutonomousLowGoal: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Collector *collector;
        Timer *autoTime;
        int crossState;

    public:
        AutonomousLowGoal(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Collector *collector) :
                IAutonomous(chooser, defaultChooser, "LowGoal"),
                driveTrain(driveTrain),
                collector(collector),
                autoTime(new Timer()),
                crossState(0)
        {
        }

        virtual ~AutonomousLowGoal()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
