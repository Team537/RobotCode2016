#ifndef PIDANGLESOURCE_HPP
#define PIDANGLESOURCE_HPP

#include <Schematic.hpp>

class PIDAngleSource: public PIDSource
{
private:
	double target;

public:
	PIDAngleSource()
	{
		target = -1;
	}

	void SetPIDSourceType(PIDSourceType pidSource);
	void SetPIDTarget(double center);
	double PIDGet();
};

#endif
