#include <Autonomous/AutonomousReach.hpp>

void AutonomousReach::Start()
{

}

bool AutonomousReach::Run(double time)
{
	switch(reachState)
	{
		case(0):
			driveTrain->AutoDrive(10);
			reachState++;
			break;
		case(1):
			reachState += driveTrain->OnTargetDistance() ? 1 : 0;
			break;
		case(2):
			driveTrain->AutoAngle(180);
			reachState++;
			break;
		case(3):
			reachState += driveTrain->OnTargetAngle() ? 1 : 0;
			break;
	}

	return reachState <= 1;
}

void AutonomousReach::Stop()
{
	driveTrain->ChangeState(DriveState::NONE);
}
