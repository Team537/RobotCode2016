#include <DriveTrain/PIDAngleOutput.hpp>

void PIDAngleOutput::PIDWrite(float output)
{
	this->output = output;
}

float PIDAngleOutput::GetOutput()
{
	return output;
}
