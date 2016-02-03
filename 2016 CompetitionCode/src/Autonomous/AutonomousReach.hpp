#ifndef AUTONOMUSTEST_HPP
#define AUTONOMUSTEST_HPP

#include <Schematic.hpp>
#include <IAutonomous.hpp>

class AutonomousReach : public IAutonomous
{
private:

public:
	AutonomousReach(SendableChooser *chooser, bool defaultChooser) : IAutonomous(chooser, defaultChooser, "Test")
	{
		ReachState = 0;
	}

	void Start();
	bool Run(double time);
	void Stop();
	int ReachState;
};

#endif