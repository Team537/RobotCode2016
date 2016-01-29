#ifndef SHOOTERVISION_HPP
#define SHOOTERVISION_HPP

#include "Schematic.hpp"

class ShooterVision
{
private:
	std::shared_ptr<NetworkTable> goalImageTable;
	double goalCenterX;
	double goalWidth;
	double goalHeight;
	double goalDistance;

public:
	ShooterVision()
	{
		goalImageTable = NetworkTable::GetTable("GRIP/myContoursReport");
		goalCenterX = 0;
		goalWidth = 0;
		goalHeight = 0;
		goalDistance = 0;
	}

	void Update();
	void Dashboard();
	double GetGoalXOffset();
	double GetGoalWidth();
	double GetGoalHeight();
	double GetGoalDistance();
};

#endif
