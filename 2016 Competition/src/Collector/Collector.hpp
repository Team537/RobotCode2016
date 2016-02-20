#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP

#include <ToolBox/RobotButton.hpp>
#include <Schematic.hpp>

class Collector: public IComponent
{
    private:
        CANTalon *collectMotor;

        RobotButton *collectInToggle;
        RobotButton *collectStop;
        RobotButton *collectOutButton;

    public:
        Collector(Joystick *joystick) :
                IComponent(joystick, new string("Collector"))
        {
            collectMotor = new CANTalon(0);

            collectInToggle = new RobotButton(joystick, JOYSTICK_A);
            collectStop = new RobotButton(joystick, JOYSTICK_B);
            collectOutButton = new RobotButton(joystick, JOYSTICK_Y);
        }

        void Update(bool teleop);
        void Dashboard();

        void Off();
        void Collect(bool reverse);
};

#endif
