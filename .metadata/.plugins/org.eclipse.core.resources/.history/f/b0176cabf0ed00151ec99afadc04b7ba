#include <Autonomous/AutonomousTimed.hpp>

void AutonomousTimed::Start()
{
    AutoTime->Reset();
    AutoTime->Start();
    SmartDashboard::PutString("Test", "Auto started");
}

bool AutonomousTimed::Run(double time)
{
    if(AutoTime->Get() < 2)
    {
        driveTrain->SetState(DriveTrain::DriveState::NONE);
        SmartDashboard::PutString("Test1", "State1");
    }
    else if(AutoTime->Get() < 10)
    {
        driveTrain->AutoTimed();
        SmartDashboard::PutString("Test2", "State2");
    }
    else
    {
        driveTrain->SetState(DriveTrain::DriveState::NONE);
        SmartDashboard::PutString("Test3", "State3");
    }
    SmartDashboard::PutNumber("Auto time 537", AutoTime->Get());
}

void AutonomousTimed::Stop()
{
    driveTrain->SetState(DriveTrain::DriveState::NONE);
}
