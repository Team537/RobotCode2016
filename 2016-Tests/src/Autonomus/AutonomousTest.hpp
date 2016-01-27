#ifndef AUTONOMUSTEST_HPP
#define AUTONOMUSTEST_HPP

#include <IAutonomous.hpp>
#include <Drive/DriveTest.hpp>

class AutonomousTest : IAutonomous {
private:
	DriveTest *driveTest;

public:
	AutonomousTest() : IAutonomous("Test") {
		driveTest = new DriveTest();
	}

	void Start();
	void Update(DriveTrain *driveTrain);
	void Stop();
};

#endif
