#include <Vision/Vision.hpp>

void Vision::Update(bool teleop)
{
	/* Gets the data from the network table. */
    ArrayRef<double> areaData = goalImageTable->GetNumberArray("area", ArrayRef<double>());
    ArrayRef<double> centerXData = goalImageTable->GetNumberArray("centerX", ArrayRef<double>());
    ArrayRef<double> widthData = goalImageTable->GetNumberArray("width", ArrayRef<double>());
    ArrayRef<double> heightData = goalImageTable->GetNumberArray("height", ArrayRef<double>());

	/* Get the pointer. */
    int pointer = 0;

    for (unsigned int i = 0; i < areaData.size(); i++)
    {
        if ((widthData[i] / heightData[i]) > 0.5f || (widthData[i] / heightData[i]) < 1.6f)
        {
            if (areaData[i] > areaData[pointer])
            {
                pointer = i;
            }
        }
    }

    /* Area. */
    if (!areaData.empty())
    {
        goalArea = areaData[pointer];
    }
    else
    {
        goalArea = 0;
    }

    /* Center X. */
    if (!centerXData.empty())
    {
        goalCenterX = centerXData[pointer];
    }
    else
    {
        goalCenterX = -1;
    }

    /* Width. */
    if (!widthData.empty())
    {
        goalWidth = widthData[pointer];
    }
    else
    {
        goalWidth = -1;
    }

    /* Height. */
    if (!heightData.empty())
    {
        goalHeight = heightData[pointer];
    }
    else
    {
        goalHeight = -1;
    }

    /* Calculate Distance. */
    goalDistance = ((GOAL_WIDTH / 12) * WEBCAM_PIXEL_WIDTH) / (2 * GetGoalWidth() * WEBCAM_TAN_FOV); // Goal width / 12 inches in a foot.
}

void Vision::Dashboard()
{
    SmartDashboard::PutNumber("Vision Goal Area (px)", GetGoalArea());
    SmartDashboard::PutNumber("Vision Goal Offset X (px)", GetGoalCenterX());
    SmartDashboard::PutNumber("Vision Goal Height (px)", GetGoalHeight());
    SmartDashboard::PutNumber("Vision Goal Width (px)", GetGoalWidth());
    SmartDashboard::PutNumber("Vision Goal Distance (ft)", GetGoalDistance());
}
