#include "Schematic.hpp"
#include "Swerve/Swerve.hpp"
#include "Shooter/Shooter.hpp"

class Robot: public IterativeRobot {
private:
	Joystick *joystick;
	AnalogGyro *gyro;
	Swerve *swerve;
	Shooter *shooter;

	SendableChooser *sendableAutonomous;
	// std::vector<IAutonomous> *autonomous;

	int autonomousSelected;

	void RobotInit() {
		joystick = new Joystick(0);
		gyro = new AnalogGyro(1);
		gyro->Reset();
		swerve = new Swerve(joystick, gyro);
		shooter = new Shooter(joystick);

		sendableAutonomous = new SendableChooser();
		// autonomous = new std::vector<IAutonomous>();
		autonomousSelected = 0;
	}

	void AddAutonomousModes() {
	// 	autonomous[autonomous->size()] = new AutonomousTest();
	}

	void AutonomousInit() {
		// for (IAutonomous a : autonomous) {
		//	sendableAutonomous->AddObject((std::basic_string) a.GetName(), a);
		// }
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
