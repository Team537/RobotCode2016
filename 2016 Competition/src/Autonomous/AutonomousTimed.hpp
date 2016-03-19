#pragma once

#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousTimed: public IAutonomous
{
    private:
        DriveTrain *driveTrain;
        Timer *autoTime;
        int crossState;

    public:
        AutonomousTimed(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) :
                IAutonomous(chooser, defaultChooser, "Timed"),
                driveTrain(driveTrain),
                autoTime(new Timer()),
                crossState(0)
        {
        }

        virtual ~AutonomousTimed()
        {
        }

        void Start();
        bool Run(const double& time);
        void Stop();
};
