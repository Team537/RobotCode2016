#include "Shooter.hpp"

void Shooter::Update() {
	vision->Update();
}

void Shooter::Shoot( bool ShooterToggle) {
	if(ShooterToggle == 1 && lastpressedShoot == false)
	{
		if(ShooterMotor->Get() == 0)
		{
			ShooterMotor->Set(.5);
		}
		if(ShooterMotor->Get() != 0)
		{
			ShooterMotor->Set(0);
		}
	}
	lastpressedShoot = ShooterToggle;
}

void Shooter::Feed(bool FeedButtonOn, bool FeedButtonOff){
	if(FeedButtonOn == 1)
	{
		Feeder->Set(1);
	}
	if(FeedButtonOff == 1)
	{
		Feeder->Set(0);
	}
	SmartDashboard::PutBoolean("Feed", FeedButtonOn);
	SmartDashboard::PutBoolean("Feeder Piston", Feeder->Get());
}

void Shooter::Dashboard() {
	vision->Dashboard();
}

bool Shooter::isActivated()
{
	return ActivateShooter;
}
