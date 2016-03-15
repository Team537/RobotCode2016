#ifndef AUTONOMOUSNONE_HPP
#define AUTONOMOUSNONE_HPP

#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/Shooter.hpp>
#include <Schematic.hpp>

class AutonomousNone: public IAutonomous
{
    private:

    public:
        AutonomousNone(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, Shooter *shooter) :
                IAutonomous(chooser, defaultChooser, "None")
        {

        }

        void Start();
        bool Run();
        void Stop();
};

#endif
