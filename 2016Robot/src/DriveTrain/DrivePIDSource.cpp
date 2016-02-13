#include <DriveTrain/DrivePIDSource.hpp>

void DrivePIDSource::SetPIDSourceType(PIDSourceType pidSource)
{
	m_pidSource = pidSource;
}

void DrivePIDSource::SetPIDTarget(double center)
{
	this->target = center;
}

double DrivePIDSource::PIDGet()
{
	return target;
}
