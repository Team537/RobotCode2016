#include "Schematic.hpp"
#include "Swerve.hpp"
#include "Shooter.hpp"

class Robot: public IterativeRobot {
private:
	Joystick *joystick;
	AnalogGyro *gyro;
	Swerve *swerve;
	Shooter* shooter;

	void RobotInit() {
		joystick = new Joystick(0);
		gyro = new AnalogGyro(1);
		swerve = new Swerve(joystick, gyro);
		shooter = new Shooter(joystick);
	}

	void AutonomousInit() {
	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {
	}

	void TeleopPeriodic() {
		shooter->Update();
		shooter->Dashboard();

		swerve->Drive(shooter);
		// swerve->Tune(swerve->frontRightAngle);
		// swerve->TuneMinMax(swerve->frontRightAngle);
		swerve->Dashboard();
	}

	void TestPeriodic() {
		TeleopPeriodic();
		LiveWindow::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot);
