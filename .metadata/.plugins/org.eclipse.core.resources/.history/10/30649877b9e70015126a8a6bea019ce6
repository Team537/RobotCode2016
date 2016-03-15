#ifndef AUTONOMOUSREACH_HPP
#define AUTONOMOUSREACH_HPP

#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousReach: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        int reachState;

    public:
        AutonomousReach(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "Cross")
        {
            this->driveTrain = driveTrain;
            reachState = 0;
        }

        void Start();
        bool Run(double time);
        void Stop();
};

#endif
