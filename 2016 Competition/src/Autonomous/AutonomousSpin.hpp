#ifndef AUTONOMOUSSPIN_HPP
#define AUTONOMOUSSPIN_HPP

#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousSpin: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        int reachState;

    public:
        AutonomousSpin(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "Reach")
        {
            this->driveTrain = driveTrain;
            reachState = 0;
        }

        void Start();bool Run(double time);
        void Stop();
};

#endif
