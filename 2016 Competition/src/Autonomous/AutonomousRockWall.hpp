#ifndef AUTONOMOUSROCKWALL_HPP
#define AUTONOMOUSROCKWALL_HPP

#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/Shooter.hpp>
#include <Schematic.hpp>

class AutonomousRockWall: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Shooter *shooter;
        int CrossState;

    public:
        AutonomousRockWall(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Shooter *shooter) :
                IAutonomous(chooser, defaultChooser, "LowBar")
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
