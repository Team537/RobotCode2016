#include <Shooter/ShooterManager.hpp>

void ShooterManager::Update(bool teleop)
{
	if (activateButton->WasDown())
	{
		activated = !activated;
	}

	if (activated && drive->GetState() != SHOOTER_TELOPERATION)
	{
		drive->ChangeState(SHOOTER_TELOPERATION);
	}

	if (activated && drive->OnTargetAngle())
	{
		activated = false;
	}
}

void ShooterManager::Dashboard()
{
	SmartDashboard::PutBoolean("Shooter Activated", activated);
}

void ShooterManager::Auto()
{
	if (drive->OnTargetAngle())
	{

	}
}

void ShooterManager::Manual()
{

}
