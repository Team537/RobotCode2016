#include <DriveTrain/PIDAngleSource.hpp>

void PIDAngleSource::SetPIDSourceType(PIDSourceType pidSource)
{
	m_pidSource = pidSource;
}

void PIDAngleSource::SetPIDTarget(double center)
{
	this->target = center;
}

double PIDAngleSource::PIDGet()
{
	return target;
}
