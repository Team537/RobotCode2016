#ifndef AUTONOMOUSROUGHTERRAIN_HPP
#define AUTONOMOUSROUGHTERRAIN_HPP

#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/Shooter.hpp>
#include <Schematic.hpp>

class AutonomousRoughTerrain: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Shooter *shooter;
        int CrossState;

    public:
        AutonomousRoughTerrain(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Shooter *shooter) :
                IAutonomous(chooser, defaultChooser, "RockWall")
        {
            this->driveTrain = driveTrain;
            this->shooter = shooter;
            CrossState = 0;
        }

        void Start();
        bool Run(double time);
        void Stop();
};

#endif
