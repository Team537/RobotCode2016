#ifndef AUTONOMOUSMOAT_HPP
#define AUTONOMOUSMOAT_HPP

#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/Shooter.hpp>
#include <Schematic.hpp>

class AutonomousMoat: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Shooter *shooter;
        int CrossState;

    public:
        AutonomousMoat(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Shooter *shooter) :
                IAutonomous(chooser, defaultChooser, "Moat")
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
