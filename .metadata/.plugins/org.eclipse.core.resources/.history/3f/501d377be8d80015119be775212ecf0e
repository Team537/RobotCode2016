#ifndef AUTONOMOUSDRIVE_HPP
#define AUTONOMOUSDEMO_HPP

#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousDemo: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        int reachState;

    public:
        AutonomousDemo(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "Drive")
        {
            this->driveTrain = driveTrain;
            reachState = 0;
        }

        void Start();
        bool Run(double time);
        void Stop();
};

#endif
