#include <Autonomous/AutonomousDrive.hpp>

void AutonomousDrive::Start()
{
}

bool AutonomousDrive::Run(double time)
{
	switch(reachState)
	{
		case(0):
			driveTrain->AutoDrive(6.0f);
			reachState++;
			break;
		case(1):
			reachState += driveTrain->OnTargetDistance() ? 1 : 0;
			break;
	}

	return reachState <= 1;
}

void AutonomousDrive::Stop()
{
	driveTrain->ChangeState(DriveTrain::DriveState::NONE);
}
