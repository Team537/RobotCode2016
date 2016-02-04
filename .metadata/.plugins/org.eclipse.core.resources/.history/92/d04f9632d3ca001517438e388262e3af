#include <Shooter/ShooterManager.hpp>

void ShooterManager::Update()
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
