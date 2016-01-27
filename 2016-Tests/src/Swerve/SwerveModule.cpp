#include "SwerveModule.hpp"

void SwerveModule::UpdatePOT() {
	if (angleTalon->GetAnalogInRaw() < potMin) {
		potMin = angleTalon->GetAnalogInRaw();
	}

	if (angleTalon->GetAnalogInRaw() > potMax) {
		potMax = angleTalon->GetAnalogInRaw();
	}
}

double SwerveModule::FixAngleValues(double angle) {
	return (angle <= 0) ? angle + 360 : angle;
}

double SwerveModule::FixOutputAngle(double angle) {
	if (angle > 330) {
		driveSign = -1;
		angle -= 180;
	} else if (angle < 30) {
		driveSign = -1;
		angle += 180;
	} else {
		driveSign = 1;
	}

	return angle;
}

double SwerveModule::CalculatePOTValue(double angle) {
	return ((angle / 360) * (potMax - potMin)) + potMin;
}

void SwerveModule::Drive(double speed, double angle) {
	UpdatePOT();
	double angleValue = FixOutputAngle(FixAngleValues(angle));
	angleTalon->Set(CalculatePOTValue(angleValue));
	driveTalon->Set(driveSign * speed * SPEED_MULTIPLIER);
}

void SwerveModule::Dashboard() {
	SmartDashboard::PutNumber(moduleName + " Angle Readings", angleTalon->GetAnalogInRaw());
	SmartDashboard::PutNumber(moduleName + " Angle Setpoint", angleTalon->GetSetpoint());

	SmartDashboard::PutNumber(moduleName + " Drive Readings", driveTalon->GetAnalogInRaw());
	SmartDashboard::PutNumber(moduleName + " Drive Velocity", driveTalon->GetAnalogInVel());
}
