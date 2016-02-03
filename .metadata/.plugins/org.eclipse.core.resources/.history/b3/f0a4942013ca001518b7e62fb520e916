#ifndef AUTONOMUSTEST_HPP
#define AUTONOMUSTEST_HPP

#include <Schematic.hpp>
#include <IAutonomous.hpp>
#include <DriveTrain/DriveTrain.hpp>

class AutonomousReach : public IAutonomous
{
private:
	int reachState;
	DriveTrain *driveTrain;

public:
	AutonomousReach(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain) : IAutonomous(chooser, defaultChooser, "Test")
	{
		reachState = 0;
		this->driveTrain = driveTrain;
	}

	void Start();
	bool Run(double time);
	void Stop();
};

#endif
