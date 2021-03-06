#include <Autonomous/AutonomousLowGoal.hpp>

void AutonomousLowGoal::Start()
{
    crossState = 0;
}

bool AutonomousLowGoal::Run(const double& time)
{
    switch (crossState)
    {
        case (0):
            if (collector->IsCollectorDeployed())
            {
                driveTrain->SetState(DriveTrain::DriveState::NONE);
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
            driveTrain->AutoDistance(24); // 150
            crossState++;
            break;
        case (3):
            crossState += driveTrain->IsWaiting() ? 1 : 0;
            break;
       /* case (4):
            driveTrain->AutoDistance(84.0f);
            CrossState++;
            break;
        case (5):
            crossState += driveTrain->IsWaiting() ? 1 : 0;
            break;*/
    }

    SmartDashboard::PutNumber("Low Goal State", crossState);

    return crossState <= 3;
}

void AutonomousLowGoal::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
