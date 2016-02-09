#ifndef VISIONMANAGER_HPP
#define VISIONMANAGER_HPP

#include <Schematic.hpp>

using namespace std;
using namespace llvm;

class VisionManager : public IComponent
{
private:
	shared_ptr<NetworkTable> goalImageTable;
	double goalArea;
	double goalCenterX;
	double goalWidth;
	double goalHeight;
	double goalDistance;

public:
	VisionManager() : IComponent(NULL, new string("Vision"))
	{
		goalImageTable = NetworkTable::GetTable("GRIP/myContoursReport");
		goalArea = 0;
		goalCenterX = 0;
		goalWidth = 0;
		goalHeight = 0;
		goalDistance = 0;
	}

	void Update(bool teleop);
	void Dashboard();

	double GetGoalArea() const
	{
		return goalArea;
	}

	double GetGoalCenterX() const
	{
		return goalCenterX;
	}

	double GetGoalDistance() const
	{
		return goalDistance;
	}

	double GetGoalHeight() const
	{
		return goalHeight;
	}

	double GetGoalWidth() const
	{
		return goalWidth;
	}
};

#endif
