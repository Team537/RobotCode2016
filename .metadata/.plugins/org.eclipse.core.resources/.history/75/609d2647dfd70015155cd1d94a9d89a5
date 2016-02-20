#include <Autonomous/AutonomousSpin.hpp>

void AutonomousSpin::Start()
{
}

bool AutonomousSpin::Run(double time)
{
    switch (reachState)
    {
        case (0):
            driveTrain->AutoAngle(90.0f);
            reachState++;
            break;
        case (1):
            reachState += driveTrain->IsAtAngle() ? 1 : 0;
            break;
    }

    return reachState <= 1;
}

void AutonomousSpin::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
