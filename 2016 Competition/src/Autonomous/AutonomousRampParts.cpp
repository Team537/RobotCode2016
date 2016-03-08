#include <Autonomous/AutonomousRampParts.hpp>

void AutonomousRampParts::Start()
{
}

bool AutonomousRampParts::Run(double time)
{
    switch (CrossState)
    {
        case (0):
            driveTrain->Cross(false, DRIVE_DEFENSE_RAMP_PARTS);
            CrossState++;
            break;
        case (1):
            CrossState += driveTrain->IsWaiting() ? 1 : 0;
            break;
        case (2):
            driveTrain->AutoDistance(12.0f);
            CrossState++;
            break;
        case (3):
            CrossState += driveTrain->IsWaiting() ? 1 : 0;
            break;
        case (4):
            shooter->AutoShoot();
            CrossState++;
            break;
        case (5):
            CrossState += !shooter->IsActivated() ? 1 : 0;
            break;
    }

    return CrossState <= 5;
}

void AutonomousRampParts::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
