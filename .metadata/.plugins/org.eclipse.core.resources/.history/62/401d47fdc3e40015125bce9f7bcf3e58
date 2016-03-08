#ifndef AUTONOMOUSBALL1_HPP
#define AUTONOMOUSBALL1_HPP

#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/Shooter.hpp>
#include <Schematic.hpp>

class AutonomousBall1: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Shooter *shooter;
        int reachState;

    public:
        AutonomousBall1(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Shooter *shooter) :
                IAutonomous(chooser, defaultChooser, "Ball1")
        {
            this->driveTrain = driveTrain;
            this->shooter = shooter;
            reachState = 0;
        }

        void Start();
        bool Run(double time);
        void Stop();
};

#endif
