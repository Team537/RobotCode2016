#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousMoat: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        int crossState;
        Collector *collector;
    public:
        AutonomousMoat(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "Moat"),
                driveTrain(driveTrain),
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
