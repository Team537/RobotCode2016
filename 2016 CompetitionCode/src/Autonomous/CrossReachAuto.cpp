#include <Autonomous/CrossReachAuto.hpp>


void CrossReachAuto::Start()
{

}

bool CrossReachAuto::Run(double time)
{
	switch(crossreachstate)
	{
		case(0):
			driveTrain->AutoDrive(10);
			crossreachstate++;
			break;
		case(1):
			crossreachstate += driveTrain->OnTargetDistance() ? 1 : 0;
			break;
		case(2):
			driveTrain->AutoAngle(180);
			crossreachstate++;
			break;
		case(3):
			crossreachstate += driveTrain->OnTargetAngle() ? 1 : 0;
			break;
	}

	return crossreachstate <= 1;
}

void CrossReachAuto::Stop()
{
	driveTrain->ChangeState(DriveState::NONE);
}
