#include <Vision/VisionManager.hpp>

void VisionManager::Update(bool teleop)
{
	/** Area. */
	ArrayRef<double> areaData = goalImageTable->GetNumberArray("area", ArrayRef<double>());
	int pointer = 0;

	for (int i = 0; i < areaData.size(); i++)
	{
		if (areaData[i] > areaData[pointer])
		{
			pointer = i;
		}
	}

	if (!areaData.empty())
	{
		goalArea = areaData[pointer];
	}
	else
	{
		goalArea = 0;
	}

	/** Center X. */
	ArrayRef<double> centerXData = goalImageTable->GetNumberArray("centerX", ArrayRef<double>());

	if (!centerXData.empty())
	{
		goalCenterX = centerXData[pointer];
	}
	else
	{
		goalCenterX = -1;
	}

	/** Width. */
	ArrayRef<double> widthData = goalImageTable->GetNumberArray("width", ArrayRef<double>());

	if (!widthData.empty())
	{
		goalWidth = widthData[pointer];
	}
	else
	{
		goalWidth = -1;
	}

	/** Height. */
	ArrayRef<double> heightData = goalImageTable->GetNumberArray("height", ArrayRef<double>());

	if (!heightData.empty())
	{
		goalHeight = heightData[pointer];
	}
	else
	{
		goalHeight = -1;
	}

	/** Calculate Distance. */
	goalDistance = ((GOAL_WIDTH / 12) * WEBCAM_PIXEL_WIDTH) / (2 * GetGoalWidth() * WEBCAM_TAN_FOV); // Goal width / 12 inches in a foot.
}

void VisionManager::Dashboard()
{
	SmartDashboard::PutNumber("Goal Area (px)", GetGoalArea());
	SmartDashboard::PutNumber("Goal Offset X (px)", GetGoalCenterX());
	SmartDashboard::PutNumber("Goal Height (px)", GetGoalHeight());
	SmartDashboard::PutNumber("Goal Width (px)", GetGoalWidth());
	SmartDashboard::PutNumber("Goal Distance (ft)", GetGoalDistance());
}
