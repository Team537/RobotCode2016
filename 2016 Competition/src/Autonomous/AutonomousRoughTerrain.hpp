#pragma once
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousRoughTerrain: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Collector *collector;
        int crossState;
    public:
        AutonomousRoughTerrain(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Collector *collector) :
                IAutonomous(chooser, defaultChooser, "RoughTerrain"),
                driveTrain(driveTrain),
                collector(collector),
                crossState(0)
        {
        }

        virtual ~AutonomousRoughTerrain()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
