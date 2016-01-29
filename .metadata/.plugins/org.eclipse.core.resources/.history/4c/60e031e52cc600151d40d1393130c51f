#ifndef DRIVETEST_HPP
#define DRIVETEST_HPP

#include "Schematic.hpp"
#include "IDrive.hpp"

class DriveTest : IDrive {
private:
	AnglePID *anglePID;
	Gyro *gyro;

public:
	DriveTest() : IDrive() {
		anglePID = new AnglePID(1);
		//gyro = new Gyro();
	}

	void Update(DriveTrain *driveTrain);
	bool AtTarget();
};

#endif
