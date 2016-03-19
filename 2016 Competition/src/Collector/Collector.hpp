#pragma once

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
                IComponent(joystickPrimary, joystickSecondary, new string("Collector")),
                collectMotor(new CANTalon(9)),
                collectInToggle(new RobotButton(joystickPrimary, JOYSTICK_A, false)),
                collectStop(new RobotButton(joystickPrimary, JOYSTICK_B, false)),
                collectOutButton(new RobotButton(joystickPrimary, JOYSTICK_Y, false)),
                reverseCollecting(false)
        {
            collectMotor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
            collectMotor->Enable();
        }

        virtual ~Collector()
        {
        }

        void Update(const bool& teleop);
        void Dashboard();

        void Collect(const bool& reverse);
        void TurnOff();
};
