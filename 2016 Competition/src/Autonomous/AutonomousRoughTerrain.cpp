#include <Autonomous/AutonomousRoughTerrain.hpp>

void AutonomousRoughTerrain::Start()
{
}

bool AutonomousRoughTerrain::Run(const double& time)
{
    switch (crossState)
    {
        case (0):
            driveTrain->Cross(false, DRIVE_DEFENSE_ROUGH_TERRAIN);
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

void AutonomousRoughTerrain::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
