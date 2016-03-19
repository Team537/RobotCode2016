#pragma once

#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousLowBar: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Timer *autoTime;
        int crossState;

    public:
        AutonomousLowBar(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "LowBar"),
                driveTrain(driveTrain),
                autoTime(new Timer()),
                crossState(0)
        {
        }

        virtual ~AutonomousLowBar()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
