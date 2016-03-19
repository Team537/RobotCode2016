#pragma once

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
                IComponent(new string("Vision")),
                goalImageTable(NetworkTable::GetTable("GRIP/myContoursReport")),
                goalArea(0),
                goalCenterX(0),
                goalWidth(0),
                goalHeight(0),
                goalDistance(0)
        {
        }

        virtual ~Vision()
        {
        }

        void Update(const bool& teleop);
        void Dashboard();

        inline double GetGoalArea() const { return goalArea; }

        inline double GetGoalCenterX() const { return goalCenterX; }

        inline double GetGoalDistance() const { return goalDistance; }

        inline double GetGoalHeight() const { return goalHeight; }

        inline double GetGoalWidth() const { return goalWidth; }
};
