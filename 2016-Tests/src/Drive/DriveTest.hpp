#ifndef DRIVETEST_HPP
#define DRIVETEST_HPP

#include "Schematic.hpp"
#include "IDrive.hpp"

class DriveTest : IDrive {
private:
	AnglePID *anglePID;
	Gyro *gyro;

public:
	DriveTest(Gyro *gyro) : IDrive() {
		anglePID = new AnglePID(1);
		this->gyro = gyro;
	}

	void Update(DriveTrain *driveTrain);
	bool AtTarget();
};

#endif
