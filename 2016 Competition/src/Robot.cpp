#include <Autonomous/AutonomousSpin.hpp>
#include <Autonomous/AutonomousDrive.hpp>
#include <Climber/Climber.hpp>
#include <Collector/Collector.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/Shooter.hpp>
#include <Vision/Vision.hpp>
#include <Schematic.hpp>

using namespace std;

class Robot: public IterativeRobot
{
	enum State { STOPED, AUTO, TELEOP, TEST };

private:
	SendableChooser* autoChooser;
	IAutonomous* selectedAuto;

	Joystick* joystickPrimary;
	Joystick* joystickSecondary;
	Compressor *compressor;
	AHRS *ahrs;

	Vision* vision;
	DriveTrain* driveTrain;
	Shooter* shooter;
	// Climber* climber;
	// Collector* collector;

	State gameState;

	void RobotInit()
	{
		// Sets up the joysticks.
		joystickPrimary = new Joystick(CONTROLLER_PRIMARY);
		joystickSecondary = new Joystick(CONTROLLER_SECONDARY);

		// Sets up robot components.
		compressor = new Compressor();

        try
        {
            ahrs = new AHRS(SPI::Port::kMXP);
            ahrs->Reset();
        }
        catch (exception e)
        {
            string err_string = "Error instantiating NavX-MXP: " + e.what();
            DriverStation::ReportError(err_string.c_str());
        }

		// Creates the robot components.
		vision = new Vision();
		driveTrain = new DriveTrain(joystickPrimary, ahrs, vision);
		shooter = new Shooter(joystickPrimary, vision, driveTrain);
		// climber = new Climber(joystickPrimary);
		// collector = new Collector(joystickPrimary);

		// Creates the auto modes.
		selectedAuto = NULL;
		autoChooser = new SendableChooser();
		new AutonomousSpin(autoChooser, true, driveTrain);
		new AutonomousDrive(autoChooser, false, driveTrain);
		SmartDashboard::PutData("Auto Modes", autoChooser);

		// Sets up the game states.
		gameState = State::STOPED;
	}

	void ComponentsUpdate()
	{
		bool isTeleop = DriverStation::GetInstance().IsOperatorControl() || DriverStation::GetInstance().IsTest();
		vision->ComponentUpdate(isTeleop);
		shooter->ComponentUpdate(isTeleop);
		// climber->ComponentUpdate(isTeleop);
		driveTrain->ComponentUpdate(isTeleop);
		// collector->ComponentUpdate(isTeleop);

		SmartDashboard::PutNumber("NavX Angle", ahrs->GetAngle());
		SmartDashboard::PutNumber("NavX Angle Pitch", ahrs->GetPitch());
		SmartDashboard::PutNumber("NavX Angle Yaw", ahrs->GetYaw());
		SmartDashboard::PutNumber("NavX Angle Roll", ahrs->GetRoll());
		SmartDashboard::PutNumber("NavX Velocity X", ahrs->GetVelocityX());
		SmartDashboard::PutNumber("NavX Velocity Y", ahrs->GetVelocityY());
		SmartDashboard::PutNumber("NavX Velocity Z", ahrs->GetVelocityZ());
	}

	void AutonomousInit()
	{
		selectedAuto = (IAutonomous*) autoChooser->GetSelected();
        ahrs->Reset();
        gameState = State::AUTO;
	}

	void AutonomousPeriodic()
	{
		SmartDashboard::PutString("Auto Selected", ((IAutonomous*) autoChooser->GetSelected())->GetName());

		if (selectedAuto != NULL)
		{
			double time = DriverStation::GetInstance().GetMatchTime();
			bool autoRunning = selectedAuto->AutonomousUpdate(time);
			selectedAuto->AutonomousDashboard();
			ComponentsUpdate();

			if (!autoRunning)
			{
				selectedAuto = NULL;
			}
		}
	}

	void TeleopInit()
	{
		if (selectedAuto != NULL)
		{
			selectedAuto->AutonomousUpdate(1000);
			selectedAuto = NULL;
		}

        ahrs->Reset();
        gameState = State::TELEOP;
	}

	void TeleopPeriodic()
	{
		ComponentsUpdate();
	}

	void TestPeriodic()
	{
		ComponentsUpdate();
		LiveWindow::GetInstance()->Run();
        gameState = State::TEST;
	}
};

START_ROBOT_CLASS(Robot)
