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

	VisionManager *vision;
	ShooterManager *shooter;
	DriveTrain *driveTrain;

	void RobotInit()
	{
		// Sets up the joysticks.
		primary = new Joystick(CONTROLLER_PRIMARY);
		secondary = new Joystick(CONTROLLER_SECONDARY);

		// Sets up robot sub components.
		vision = new VisionManager();
		shooter = new ShooterManager(primary, vision);
		driveTrain = new DriveTrain(primary, shooter);

		// Sets up auto modes.
		selectedAuto = NULL;
		autoChooser = new SendableChooser();
		new AutonomousReach(autoChooser, true);
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
		vision->ComponentUpdate();
		shooter->ComponentUpdate();
		driveTrain->ComponentUpdate();
	}

	void TestPeriodic()
	{
		TeleopPeriodic();
		LiveWindow::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot)