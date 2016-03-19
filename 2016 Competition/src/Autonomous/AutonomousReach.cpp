#include <Autonomous/AutonomousReach.hpp>

void AutonomousReach::Start()
{
}

bool AutonomousReach::Run(const double& time)
{
    switch (reachState)
    {
        case (0):
            driveTrain->Cross(false, DRIVE_DEFENSE_ROCK_WALL);
            reachState++;
            break;
        case (1):
            reachState += driveTrain->IsWaiting() ? 1 : 0;
            break;
        case (2):
            driveTrain->AutoDistance(50.0f);
            reachState++;
            break;
        case (3):
            reachState += driveTrain->IsWaiting() ? 1 : 0;
            break;
    }

    return reachState <= 3;
}

void AutonomousReach::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
