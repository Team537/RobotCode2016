#ifndef AUTONOMOUSDRIVE_HPP
#define AUTONOMOUSDRIVE_HPP

#include <DriveTrain/DriveTrain.hpp>
#include <Schematic.hpp>

class AutonomousDrive: public IAutonomous
{
private:
	DriveTrain *driveTrain;
	int reachState;

public:
	AutonomousDrive(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) : IAutonomous(chooser, defaultChooser, "Reach")
	{
		this->driveTrain = driveTrain;
		reachState = 0;
	}

	void Start();
	bool Run(double time);
	void Stop();
};

#endif
