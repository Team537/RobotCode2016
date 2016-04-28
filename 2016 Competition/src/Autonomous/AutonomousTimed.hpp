#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousTimed: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Collector *collector;
        Timer *autoTime;
        int crossState;
    public:
        AutonomousTimed(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Collector *collector) :
                IAutonomous(chooser, defaultChooser, "Timed"),
                driveTrain(driveTrain),
                collector(collector),
                autoTime(new Timer()),
                crossState(0)
        {
        }

        virtual ~AutonomousTimed()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
