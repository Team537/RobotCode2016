#ifndef AUTONOMUSTEST_HPP
#define AUTONOMUSTEST_HPP

#include <IAutonomous.hpp>

class AutonomousTest : IAutonomous {
private:

public:
	AutonomousTest() : IAutonomous("Test") {
	}

	void Start();
	void Update();
	void Stop();
};

#endif
