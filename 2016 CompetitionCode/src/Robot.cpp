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
	ShooterManager *shooter;
	DriveTrain *driveTrain;

	void RobotInit()
	{
		// Sets up the joysticks.
		primary = new Joystick(CONTROLLER_PRIMARY);
		secondary = new Joystick(CONTROLLER_SECONDARY);

		// Sets up robot sub components.
		gyro = new AnalogGyro(0);
		vision = new VisionManager();
		shooter = new ShooterManager(primary, vision);
		driveTrain = new DriveTrain(primary, gyro, shooter);

		// Sets up auto modes.
		selectedAuto = NULL;
		autoChooser = new SendableChooser();
		new AutonomousReach(autoChooser, true, driveTrain);
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
		driveTrain->ComponentUpdate(teleop);
	}

	void TestPeriodic()
	{
		ComponentsUpdate();
		LiveWindow::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot)
