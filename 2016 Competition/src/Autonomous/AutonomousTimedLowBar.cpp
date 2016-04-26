#include <Autonomous/AutonomousTimedLowBar.hpp>

void AutonomousTimedLowBar::Start()
{
    if (collector->IsCollectorDeployed())
    {
        autoTime->Reset();
        autoTime->Start();
        SmartDashboard::PutString("Test", "Auto started");
    }
}

bool AutonomousTimedLowBar::Run(const double& time)
{
    if(autoTime->Get() < 2)
    {
        driveTrain->SetState(DriveTrain::DriveState::NONE);
        SmartDashboard::PutString("Test1", "State1");
    }
    else if(autoTime->Get() < 5)
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
    return autoTime->Get() <= 4;
}

void AutonomousTimedLowBar::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
