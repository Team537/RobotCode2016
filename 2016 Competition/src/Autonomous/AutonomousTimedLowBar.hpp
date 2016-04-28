#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousTimedLowBar: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Collector *collector;
        Timer *autoTime;
        int crossState;
    public:
        AutonomousTimedLowBar(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Collector *collector) :
                IAutonomous(chooser, defaultChooser, "Timed"),
                driveTrain(driveTrain),
                collector(collector),
                autoTime(new Timer()),
                crossState(0)
        {
        }

        virtual ~AutonomousTimedLowBar()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
