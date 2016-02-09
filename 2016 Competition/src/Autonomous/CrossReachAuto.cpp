#include <Autonomous/CrossReachAuto.hpp>


void CrossReachAuto::Start()
{

}

bool CrossReachAuto::Run(double time, Gyro *gyro)
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
			crossreachstate += gyro->GetAngle() <= 5 ? 1 : 0;
			crossreachstate++;
			break;
		case(3):
				//Shoot Da Ball
						/*
						 * we don't know how this will be done
						 */
			break;
		case(4):
			crossreachstate += driveTrain->OnTargetAngle() ? 1 : 0;
			break;
	}

	return crossreachstate <= 1;
}

void CrossReachAuto::Stop()
{
	driveTrain->ChangeState(DriveState::NONE);
}
