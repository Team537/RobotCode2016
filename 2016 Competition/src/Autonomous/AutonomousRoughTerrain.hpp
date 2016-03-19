#pragma once

#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousRoughTerrain: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        int crossState;

    public:
        AutonomousRoughTerrain(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "RoughTerrain"),
                driveTrain(driveTrain),
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
