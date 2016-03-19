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
        Collector() :
                IComponent(new string("Collector")),
                collectMotor(new CANTalon(9)),
                collectInToggle(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_A)),
                collectStop(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_B)),
                collectOutButton(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_Y)),
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
