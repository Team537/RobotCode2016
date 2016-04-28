#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousTimedLowBar: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Timer *autoTime;
        int crossState;
        Collector *collector;
    public:
        AutonomousTimedLowBar(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "Timed"),
                driveTrain(driveTrain),
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
