#ifndef SHOOTER_HPP
#define SHOOTER_HPP

#include "Schematic.hpp"
#include "Shooter/ShooterVision.hpp"

class Shooter {
private:

	Victor *ShooterMotor;
	Solenoid *Feeder;
	ShooterVision *vision;


public:
	Shooter() {
		ShooterMotor = new Victor (8);
		Feeder = new Solenoid(4);
		vision = new ShooterVision();
		lastpressedShoot = false;
		lastpressedFeed = false;
		ActivateShooter = false;
	}

	void Update();
	void Dashboard();
	void Shoot(bool ShooterToggle);
	void Feed(bool FeedButtonOn, bool FeedButtonOff);
	bool isActivated();
	bool lastpressedShoot;
	bool lastpressedFeed;
	bool ActivateShooter;

	inline ShooterVision* GetVision() { return vision; }
};

#endif
