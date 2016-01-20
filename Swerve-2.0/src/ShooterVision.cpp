#include "ShooterVision.hpp"

void ShooterVision::Update() {
	/** Center X */
	llvm::ArrayRef<double> centerXData = goalImageTable->GetNumberArray("centerX", llvm::ArrayRef<double>());

	if (!centerXData.empty()) {
		goalCenterX = centerXData[0];
	} else {
		goalCenterX = -1;
	}

	/** Width */
	llvm::ArrayRef<double> widthData = goalImageTable->GetNumberArray("width", llvm::ArrayRef<double>());

	if (!widthData.empty()) {
		goalWidth = widthData[0];
	} else {
		goalWidth = -1;
	}

	/** Height */
	llvm::ArrayRef<double> heightData = goalImageTable->GetNumberArray("height", llvm::ArrayRef<double>());

	if (!heightData.empty()) {
		goalHeight = heightData[0];
	} else {
		goalHeight = -1;
	}

	/** Calculate Distance */
	goalDistance = ((GOAL_WIDTH / 12) * WEBCAM_PIXEL_WIDTH) / (2 * GetGoalWidth() * TAN_FOV); // Goal width / 12 inches in a foot.
}

void ShooterVision::Dashboard() {
	SmartDashboard::PutNumber("X Offset", GetGoalXOffset());
	SmartDashboard::PutNumber("Goal Height", GetGoalHeight());
	SmartDashboard::PutNumber("Goal Width", GetGoalWidth());
	SmartDashboard::PutNumber("Target Distance", GetGoalDistance());
}

double ShooterVision::GetGoalXOffset() {
	return goalCenterX;
}

double ShooterVision::GetGoalWidth() {
	return goalWidth;
}

double ShooterVision::GetGoalHeight() {
	return goalHeight;
}

double ShooterVision::GetGoalDistance() {
	return goalDistance;
}
