#include <Autonomous/AutonomousReach.hpp>

void AutonomousReach::Start()
{

}

bool AutonomousReach::Run(double time)
{
	switch(reachState)
	{
		case(0):
			bool finished = driveTrain->AutoDrive(10);
			reachState += finished ? 1 : 0;
			break;
		case(1):
			bool finished = driveTrain->AutoAngle(180);
			reachState += finished ? 1 : 0;
			break;
	}

	return reachState <= 1;
}

void AutonomousReach::Stop()
{
	driveTrain->DisablePIDs();
}
