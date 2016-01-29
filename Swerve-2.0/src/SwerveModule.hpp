#ifndef SWERVEMODULE_HPP
#define SWERVEMODULE_HPP

#include "Schematic.hpp"

class SwerveModule {
private:
	CANTalon *driveTalon, *angleTalon;
	std::string moduleName;
	float potMin, potMax;
	int driveSign;

	void UpdatePOT();
	double FixAngleValues(double angle);
	double FixOutputAngle(double angle);
	double CalculatePOTValue(double angle);

public:
	SwerveModule(std::string name, int drivePort, int anglePort) {
		/* Drive Talon */
		driveTalon = new CANTalon(drivePort);
		driveTalon->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		driveTalon->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);

		/* Angle Talon */
		angleTalon = new CANTalon(anglePort);
		angleTalon->SetControlMode(CANTalon::ControlMode::kPosition);
		angleTalon->SetFeedbackDevice(CANTalon::FeedbackDevice::AnalogPot);

		if (DRIVE_ENABLED) {
			driveTalon->EnableControl();
		} else {
			driveTalon->Disable();
		}

		if (STEER_ENABLED) {
			angleTalon->EnableControl();
		} else {
			angleTalon->Disable();
		}

		/* Module Values. */
		moduleName = name;

		/* POT Values. */
		potMin = 50;
		potMax = 975;
		driveSign = 1;
	}

	void Drive(double speed, double angle);
	void Dashboard();

	inline CANTalon* getDriveTalon() {
		return driveTalon;
	}
	inline CANTalon* getAngleTalon() {
		return angleTalon;
	}
};

#endif
