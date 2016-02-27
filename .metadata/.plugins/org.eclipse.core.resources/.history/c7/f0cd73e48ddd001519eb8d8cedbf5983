#include <Autonomous/AutonomousBall1.hpp>

void AutonomousBall1::Start()
{
}

bool AutonomousBall1::Run(double time)
{
    switch (reachState)
    {
        case (0):
            driveTrain->Cross(false);
            reachState++;
            break;
        case (1):
            reachState += driveTrain->IsWaiting() ? 1 : 0;
            break;
        case (2):
            driveTrain->AutoDistance(72.0f);
            reachState++;
            break;
        case (3):
            reachState += driveTrain->IsWaiting() ? 1 : 0;
            break;
        case (4):
            shooter->AutoShoot();
            reachState++;
            break;
        case (5):
            reachState += !shooter->IsActivated() ? 1 : 0;
            break;
    }

    return reachState <= 5;
}

void AutonomousBall1::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
