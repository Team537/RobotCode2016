#include <Autonomous/AutonomousDrive.hpp>

void AutonomousDrive::Start()
{
}

bool AutonomousDrive::Run(double time)
{
    switch (reachState)
    {
        case (0):
            driveTrain->AutoDistance(2.0f);
            reachState++;
            break;
        case (1):
            reachState += driveTrain->IsAtDistance() ? 1 : 0;
            break;
    }

    return reachState <= 1;
}

void AutonomousDrive::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
