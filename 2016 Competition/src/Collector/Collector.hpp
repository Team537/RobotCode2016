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

        bool reverseCollecting;

    public:
        Collector(Joystick* joystickPrimary, Joystick* joystickSecondary) :
                IComponent(joystickPrimary, joystickSecondary, new string("Collector"))
        {
            collectMotor = new CANTalon(9);
            collectMotor->SetControlMode(CANTalon::ControlMode::kPercentVbus);

            collectInToggle = new RobotButton(joystickPrimary, JOYSTICK_A);
            collectStop = new RobotButton(joystickPrimary, JOYSTICK_B);
            collectOutButton = new RobotButton(joystickPrimary, JOYSTICK_Y);

            reverseCollecting = false;
        }

        void Update(bool teleop);
        void Dashboard();

        void Collect(bool reverse);
        void TurnOff();
};

#endif
