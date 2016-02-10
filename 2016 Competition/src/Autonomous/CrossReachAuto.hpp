#ifndef CROSSREACHAUTO_HPP
#define CROSSREACHAUTO_HPP

#include "Schematic.hpp"
#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/ShooterManager.hpp>

class CrossReachAuto : IAutonomous
{
private:
	ShooterManager *shoot;
	DriveTrain *driveTrain;
	int crossreachstate;

public:
	CrossReachAuto(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, ShooterManager *shoot) : IAutonomous(chooser, defaultChooser, "Test")
	{
		crossreachstate = 0;
		this->shoot = shoot;
		this->driveTrain = driveTrain;
	}

	void Start();
	bool Run(double time, Gyro *gyro);
	void Stop();
};

#endif