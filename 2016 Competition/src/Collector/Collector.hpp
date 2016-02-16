#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP

#include <ToolBox/RobotButton.hpp>
#include <Schematic.hpp>

class Collector: public IComponent
{
    private:
        Solenoid *piston;
        Victor *leftMotor, *rightMotor;
        RobotButton *extendButton, *leftCollectButton, *rightCollectButton;
        float speed;

    public:
        Collector(Joystick *joystick) :
                IComponent(joystick, new string("Collector"))
        {
            piston = new Solenoid(1);
            leftMotor = new Victor(1);
            rightMotor = new Victor(2);
            extendButton = new RobotButton(joystick, 7);
            leftCollectButton = new RobotButton(joystick, 6);
            rightCollectButton = new RobotButton(joystick, 5);
            speed = 0;
        }

        void Update(bool teleop);
        void Dashboard();

        void Reset();
        void Extend();
        void CollectLeft();
        void CollectRight();

        bool IsExtended();
};

#endif
