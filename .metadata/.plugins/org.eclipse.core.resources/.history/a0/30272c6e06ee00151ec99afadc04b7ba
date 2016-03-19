#ifndef VISION_HPP
#define VISION_HPP

#include <Schematic.hpp>

using namespace std;
using namespace llvm;

class Vision: public IComponent
{
    private:
        shared_ptr<NetworkTable> goalImageTable;
        double goalArea;
        double goalCenterX;
        double goalWidth;
        double goalHeight;
        double goalDistance;

    public:
        Vision() :
                IComponent(NULL, NULL, new string("Vision"))
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

        inline double GetGoalArea()
        {
            return goalArea;
        }

        inline double GetGoalCenterX()
        {
            return goalCenterX;
        }

        inline double GetGoalDistance()
        {
            return goalDistance;
        }

        inline double GetGoalHeight()
        {
            return goalHeight;
        }

        inline double GetGoalWidth()
        {
            return goalWidth;
        }
};

#endif
