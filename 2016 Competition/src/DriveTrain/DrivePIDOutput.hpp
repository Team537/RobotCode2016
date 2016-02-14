#ifndef SRC_DRIVETRAIN_DRIVEPIDOUTPUT_HPP_
#define SRC_DRIVETRAIN_DRIVEPIDOUTPUT_HPP_

#include <Schematic.hpp>

class DrivePIDOutput: public PIDOutput
{
private:
	float output;

public:
	DrivePIDOutput()
	{
		output = 0;
	}

	void PIDWrite(float output);
	float GetOutput();
};

#endif
