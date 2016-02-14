#ifndef PIDANGLEOUTPUT_HPP
#define PIDANGLEOUTPUT_HPP

#include <Schematic.hpp>

class PIDAngleOutput: public PIDOutput
{
private:
	float output;

public:
	PIDAngleOutput()
	{
		output = 0;
	}

	void PIDWrite(float output);
	float GetOutput();
};

#endif
