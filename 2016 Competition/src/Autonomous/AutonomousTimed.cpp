#include <Autonomous/AutonomousTimed.hpp>

void AutonomousTimed::Start()
{
    autoTime->Reset();
    autoTime->Start();
    SmartDashboard::PutString("Test", "Auto started");
}

bool AutonomousTimed::Run(const double& time)
{
    if(autoTime->Get() < 2)
    {
        driveTrain->SetState(DriveTrain::DriveState::NONE);
        SmartDashboard::PutString("Test1", "State1");
    }
    else if(autoTime->Get() < 7)
    {
        driveTrain->AutoTimed();
        SmartDashboard::PutString("Test2", "State2");
    }
    else
    {
        driveTrain->SetState(DriveTrain::DriveState::NONE);
        SmartDashboard::PutString("Test3", "State3");
    }

    SmartDashboard::PutNumber("Auto time 537", autoTime->Get());
    return autoTime->Get() <= 7;
}

void AutonomousTimed::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
