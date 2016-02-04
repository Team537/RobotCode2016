#ifndef SHOOTERMANAGER_HPP
#define SHOOTERMANAGER_HPP

#include <Schematic.hpp>
#include <Vision/VisionManager.hpp>
#include <Toolbox/MyButton.hpp>

using namespace std;

class ShooterManager : public IComponent
{
private:
	VisionManager *vision;
	MyButton *activateButton;
	bool activated;

public:
	ShooterManager(Joystick *joystick, VisionManager *vision) : IComponent(joystick, new string("Shooter"))
	{
		this->vision = vision;
		activateButton = new MyButton(joystick, 10);
		activated = false;
	}

	void Update(bool teleop);
	void Dashboard();

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
