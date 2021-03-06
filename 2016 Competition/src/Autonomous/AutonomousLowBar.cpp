#include <Autonomous/AutonomousLowBar.hpp>

void AutonomousLowBar::Start()
{
}

bool AutonomousLowBar::Run(const double& time)
{
    switch (crossState)
    {
        case (0):
            if (collector->IsCollectorDeployed())
            {
                autoTime->Reset();
                autoTime->Start();
                crossState++;
            }
            break;
        case (1):
            if (autoTime->Get() > 2.0)
            {
                autoTime->Stop();
                crossState++;
            }
            break;
        case (2):
            driveTrain->Cross(false, DRIVE_DEFENSE_LOW_BAR);
            crossState++;
            break;
        case (3):
           // crossState += driveTrain->IsWaiting() ? 1 : 0;
            break;
       /* case (4):
            driveTrain->AutoDistance(84.0f);
            CrossState++;
            break;
        case (5):
            crossState += driveTrain->IsWaiting() ? 1 : 0;
            break;*/
    }

    return crossState <= 3;
}

void AutonomousLowBar::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
