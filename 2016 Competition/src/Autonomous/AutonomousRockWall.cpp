#include <Autonomous/AutonomousRockWall.hpp>

void AutonomousRockWall::Start()
{
}

bool AutonomousRockWall::Run(const double& time)
{
    switch (crossState)
    {
        case (0):
            driveTrain->Cross(false, DRIVE_DEFENSE_ROCK_WALL);
            crossState++;
            break;
        case (1):
            crossState += driveTrain->IsWaiting() ? 1 : 0;
            break;
        case (2):
            driveTrain->AutoDistance(84.0f);
            crossState++;
            break;
        case (3):
            crossState += driveTrain->IsWaiting() ? 1 : 0;
            break;
    }

    return crossState <= 3;
}

void AutonomousRockWall::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
