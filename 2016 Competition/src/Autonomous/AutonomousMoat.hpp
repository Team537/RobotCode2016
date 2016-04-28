#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousMoat: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Collector *collector;
        int crossState;
    public:
        AutonomousMoat(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Collector *collector) :
                IAutonomous(chooser, defaultChooser, "Moat"),
                driveTrain(driveTrain),
                collector(collector),
                crossState(0)
        {
        }

        virtual ~AutonomousMoat()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
