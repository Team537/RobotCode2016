#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousRockWall: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Collector *collector;
        int crossState;
    public:
        AutonomousRockWall(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Collector *collector) :
                IAutonomous(chooser, defaultChooser, "RockWall"),
                driveTrain(driveTrain),
                collector(collector),
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
