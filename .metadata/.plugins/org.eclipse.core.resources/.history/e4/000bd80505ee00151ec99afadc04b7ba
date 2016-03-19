#ifndef AUTONOMOUSRAMPPARTS_HPP
#define AUTONOMOUSRAMPPARTS_HPP

#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/Shooter.hpp>
#include <Schematic.hpp>

class AutonomousRampParts: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Shooter *shooter;
        int CrossState;

    public:
        AutonomousRampParts(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Shooter *shooter) :
                IAutonomous(chooser, defaultChooser, "RampParts")
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
