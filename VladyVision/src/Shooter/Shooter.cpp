#include "Shooter.hpp"

void Shooter::Update() {
	vision->Update();
}

void Shooter::Shoot() {
	if(joystick->GetRawButton(5) == 1 && lastpressedShoot == false)
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
	lastpressedShoot = joystick->GetRawButton(5);
}

void Shooter::Feed(){
	if(joystick->GetRawButton(6) == 1 && lastpressedFeed == false)
	{
		Feeder->Set(!Feeder->Get());
	}
	lastpressedFeed = joystick->GetRawButton(6);
}

void Shooter::Dashboard() {
	vision->Dashboard();
}
