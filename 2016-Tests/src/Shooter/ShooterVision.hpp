#ifndef SHOOTERVISION_HPP
#define SHOOTERVISION_HPP

#include "Schematic.hpp"

class ShooterVision {
private:
	std::shared_ptr<NetworkTable> goalImageTable;
	double goalArea;
	double goalCenterX;
	double goalWidth;
	double goalHeight;
	double goalDistance;

public:
	ShooterVision() {
		goalImageTable = NetworkTable::GetTable("GRIP/myContoursReport");
		goalArea = 0;
		goalCenterX = 0;
		goalWidth = 0;
		goalHeight = 0;
		goalDistance = 0;
	}

	void Update();
	void Dashboard();

	double GetGoalArea() const {
		return goalArea;
	}

	double GetGoalCenterX() const {
		return goalCenterX;
	}

	double GetGoalDistance() const {
		return goalDistance;
	}

	double GetGoalHeight() const {
		return goalHeight;
	}

	double GetGoalWidth() const {
		return goalWidth;
	}
};

#endif
