#include <Autonomous/AutonomousMoat.hpp>

void AutonomousMoat::Start()
{
}

bool AutonomousMoat::Run(const double& time)
{
    switch (crossState)
    {
        case (0):
            if (collector->IsCollectorDeployed())
            {
                driveTrain->Cross(false, DRIVE_DEFENSE_MOAT);
                crossState++;
                break;
            }
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

void AutonomousMoat::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
