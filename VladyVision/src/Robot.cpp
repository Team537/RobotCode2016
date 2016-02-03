#include "Schematic.hpp"
#include "DriveTrain.hpp"
#include "Shooter/Shooter.hpp"

class Robot: public SampleRobot
{
	Joystick *Stick;
	DriveTrain *TankDrive;
	Shooter *WheelShooter;

public:
	Robot()
	{
		Stick = new Joystick(PRIMARY_CONTROLLER);
		TankDrive = new DriveTrain(Stick);
		WheelShooter = new Shooter();
	}

	void RobotInit()
	{

	}


	void Autonomous()
	{


	}


	void OperatorControl()
	{
		while (IsOperatorControl())
		{
			TankDrive->Drive();
			TankDrive->FirePiston(Stick->GetRawButton(3), Stick->GetRawButton(4));
		}
	}

	void Test()
	{

	}
};

START_ROBOT_CLASS(Robot)
