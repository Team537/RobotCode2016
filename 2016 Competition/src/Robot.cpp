#include <Schematic.hpp>
#include <Autonomous/AutonomousReach.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/ShooterManager.hpp>
#include <Vision/VisionManager.hpp>

class Robot: public IterativeRobot
{
private:
	SendableChooser *autoChooser;
	IAutonomous *selectedAuto;

	Joystick *primary;
	Joystick *secondary;

	AnalogGyro *gyro;
	VisionManager *vision;
	DriveTrain *drive;
	ShooterManager *shooter;

	void RobotInit()
	{
		// Sets up the joysticks.
		primary = new Joystick(CONTROLLER_PRIMARY);
		secondary = new Joystick(CONTROLLER_SECONDARY);

		// Sets up robot sub components.
		gyro = new AnalogGyro(0);
		vision = new VisionManager();
		drive = new DriveTrain(primary, gyro, vision);
		shooter = new ShooterManager(primary, vision, drive);

		// Sets up auto modes.
		selectedAuto = NULL;
		autoChooser = new SendableChooser();
		new AutonomousReach(autoChooser, true, drive);
		SmartDashboard::PutData("Auto Modes", autoChooser);
	}

	void AutonomousInit()
	{
		selectedAuto = (IAutonomous*) autoChooser->GetSelected();
	}

	void AutonomousPeriodic()
	{
		SmartDashboard::PutString("Auto Selected", ((IAutonomous*) autoChooser->GetSelected())->GetName());

		if (selectedAuto != NULL)
		{
			double time = DriverStation::GetInstance().GetMatchTime();
			bool autoRunning = selectedAuto->AutonomousUpdate(time);
			ComponentsUpdate();

			if (!autoRunning)
			{
				selectedAuto = NULL;
			}
		}
	}

	void TeleopInit()
	{
		if (selectedAuto == NULL)
		{
			selectedAuto->AutonomousUpdate(1000);
			selectedAuto = NULL;
		}
	}

	void TeleopPeriodic()
	{
		ComponentsUpdate();
	}

	void ComponentsUpdate()
	{
		bool teleop = DriverStation::GetInstance().IsOperatorControl();
		vision->ComponentUpdate(teleop);
		shooter->ComponentUpdate(teleop);
		drive->ComponentUpdate(teleop);
	}

	void TestPeriodic()
	{
		ComponentsUpdate();
		LiveWindow::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot)
