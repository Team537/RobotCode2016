#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousRockWall: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        int crossState;
        Collector *collector;
    public:
        AutonomousRockWall(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "RockWall"),
                driveTrain(driveTrain),
                crossState(0)
        {
        }

        virtual ~AutonomousRockWall()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
