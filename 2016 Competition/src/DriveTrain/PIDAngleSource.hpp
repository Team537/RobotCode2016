#ifndef DRIVEPIDSOURCE_HPP
#define DRIVEPIDSOURCE_HPP

#include <Schematic.hpp>

class DrivePIDSource: public PIDSource
{
private:
	double target;

public:
	DrivePIDSource()
	{
		target = -1;
	}

	void SetPIDSourceType(PIDSourceType pidSource);
	void SetPIDTarget(double center);
	double PIDGet();
};

#endif
