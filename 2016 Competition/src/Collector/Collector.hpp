#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP

#include <ToolBox/RobotButton.hpp>
#include <Schematic.hpp>

class Collector: public IComponent
{
    private:
        CANTalon *collectMotor;
        RobotButton *CollectButton;
        float speed;

    public:
        Collector(Joystick *joystick) :
                IComponent(joystick, new string("Collector"))
        {
            collectMotor = new CANTalon(2);
            CollectButton = new RobotButton(joystick, 5);
            speed = 0;
        }

        void Update(bool teleop);
        void Dashboard();

        void Off();
        void Collect();

        bool IsExtended();
};

#endif
