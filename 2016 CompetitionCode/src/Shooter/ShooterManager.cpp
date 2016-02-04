#include <Shooter/ShooterManager.hpp>

void ShooterManager::Update(bool teleop)
{
	if (activateButton->WasDown())
	{
		activated = !activated;
	}
}

void ShooterManager::Dashboard()
{
	SmartDashboard::PutBoolean("Shooter Activated", activated);
}
