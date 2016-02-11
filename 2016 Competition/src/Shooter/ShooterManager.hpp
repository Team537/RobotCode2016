#ifndef SHOOTERMANAGER_HPP
#define SHOOTERMANAGER_HPP

#include <Schematic.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Toolbox/MyButton.hpp>
#include <Vision/VisionManager.hpp>

using namespace std;

class ShooterManager : public IComponent
{
private:
	VisionManager *vision;
	DriveTrain *drive;
	MyButton *activateButton;
	bool activated;

public:
	ShooterManager(Joystick *joystick, VisionManager *vision, DriveTrain *drive) : IComponent(joystick, new string("Shooter"))
	{
		this->vision = vision;
		this->drive = drive;
		activateButton = new MyButton(joystick, 10);
		activated = false;
		ShooterState = 0;
	}

	void Update(bool teleop);
	void Dashboard();
	void Auto();
	void Manual();
	int ShooterState;

	VisionManager* GetVision() const
	{
		return vision;
	}

	bool IsActivated() const
	{
		return activated;
	}
};

#endif
