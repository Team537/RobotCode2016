#pragma once

#include <ToolBox/RobotButton.hpp>
#include <Schematic.hpp>


class Collector: public IComponent
{
    private:
        CANTalon *collectMotor;
        CANTalon *positionMotor;

        RobotButton *collectInToggle;
        RobotButton *collectStop;
        RobotButton *collectOutButton;
        RobotButton *toggleDeploy;
        RobotButton *retractToFrame;

        bool reverseCollecting;
        bool deployed;
        int returnState;

    public:
        enum CollectorState
        {
            INIT, RETRACT, DEPLOY_HALF, DEPLOY_FULL, TEST
        };

        CollectorState collectState;

        Collector() :
                IComponent(new string("Collector")),
                collectMotor(new CANTalon(8)),
                positionMotor(new CANTalon(7)),
                collectInToggle(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_A)),
                collectStop(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_B)),
                collectOutButton(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_Y)),
                toggleDeploy(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUTTON_LEFT)),
                retractToFrame(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUTTON_RIGHT)),
                reverseCollecting(false),
                deployed(false),
                returnState(0),
                collectState(TEST)
        {
            positionMotor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
            positionMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            positionMotor->ConfigRevLimitSwitchNormallyOpen(true);
            positionMotor->SetPID(20, 0, 0, 0);
            positionMotor->ConfigEncoderCodesPerRev(1);
            positionMotor->ConfigLimitMode(CANTalon::LimitMode::kLimitMode_SoftPositionLimits);
            positionMotor->ConfigForwardLimit(0);
            positionMotor->ConfigReverseLimit(-6130);
            positionMotor->SetPosition(0);
            positionMotor->Enable();

            collectMotor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
            collectMotor->Enable();
        }

        virtual ~Collector()
        {
        }

        void Update(const bool& teleop);
        void Dashboard();

        void Collect(const bool& reverse);
        void DeployCollector();
        void HalfRetractCollector();
        void RetractCollector();
        void TurnOff();
        void SetState(const int &state);
        bool IsCollecting();
        void collectorInit();
        bool IsCollectorDeployed();
};
