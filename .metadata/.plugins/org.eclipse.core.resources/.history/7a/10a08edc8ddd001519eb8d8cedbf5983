#include <Autonomous/AutonomousDemo.hpp>

void AutonomousDemo::Start()
{
}

bool AutonomousDemo::Run(double time)
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
            driveTrain->AutoDistance(45.0f);
            reachState++;
            break;
        case (3):
            reachState += driveTrain->IsWaiting() ? 1 : 0;
            break;
        case (4):
            driveTrain->AutoAngle(90.0f);
            reachState++;
            break;
        case (5):
            reachState += driveTrain->IsWaiting() ? 1 : 0;
            break;
    }

    return reachState <= 5;
}

void AutonomousDemo::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
