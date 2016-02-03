#ifndef AUTONOMUSTEST_HPP
#define AUTONOMUSTEST_HPP

#include <IAutonomous.hpp>

class AutonomousReach : IAutonomous {
private:

public:
	AutonomousReach() : IAutonomous("Test") {
	}

	void Start();
	void Update();
	void Stop();
};

#endif
