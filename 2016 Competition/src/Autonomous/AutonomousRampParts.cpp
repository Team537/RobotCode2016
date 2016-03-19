#include <Autonomous/AutonomousRampParts.hpp>

void AutonomousRampParts::Start()
{
}

bool AutonomousRampParts::Run(const double& time)
{
    switch (crossState)
    {
        case (0):
            driveTrain->Cross(false, DRIVE_DEFENSE_RAMP_PARTS);
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

void AutonomousRampParts::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
