#include <Autonomous/AutonomousSpin.hpp>

void AutonomousSpin::Start()
{
}

bool AutonomousSpin::Run(double time)
{
	switch(reachState)
	{
		case(0):
			driveTrain->AutoAngle(90.0f);
			reachState++;
			break;
		case(1):
			reachState += driveTrain->OnTargetAngle() ? 1 : 0;
			break;
	}

	return reachState <= 1;
}

void AutonomousSpin::Stop()
{
	driveTrain->ChangeState(DriveTrain::DriveState::NONE);
}
