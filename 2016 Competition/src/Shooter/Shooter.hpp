/*#pragma once

#include <Schematic.hpp>
#include <DriveTrain/DriveTrain.hpp>
#include <Toolbox/RobotButton.hpp>
#include <Vision/Vision.hpp>

class Shooter: public IComponent
{
    private:
        Vision *vision;
        DriveTrain *drive;

        CANTalon *talon1, *talon2;
        Solenoid *extendSolenoid;

        Timer *extendTimer;
        float spinSpeed, manualSpeed;
        bool autoAdvance;

        RobotButton *gotoNoneButton0, *gotoNoneButton1, *autoShootButton, *manualAimButton, *manualFireButton,
        *manualRetractButton, *manualOnButton, *speedUpButton, *speedDownButton, *manualOffButton;

    public:
        enum ShooterState
        {
            NONE, AIMING, SPINNING, FIRE, MANUAL
        };

        ShooterState state;

        Shooter(Vision *vision, DriveTrain *drive) :
                IComponent(new string("Shooter")),
                vision(vision),
                drive(drive),
                talon1(new CANTalon(7)),
                talon2(new CANTalon(8)),
                extendSolenoid(new Solenoid(1)),
                extendTimer(new Timer()),
                spinSpeed(50.0f),
                manualSpeed(1.0f),
                autoAdvance(false),
                gotoNoneButton0(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_B)),
                gotoNoneButton1(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_B)),
                autoShootButton(new RobotButton(RobotButton::JoystickType::PRIMARY, NEW_JOYSTICK ? RobotButton::ControlTypes::AXIS : RobotButton::ControlTypes::KEY, JOYSTICK_TRIGGER_LEFT)),
                manualAimButton(new RobotButton(RobotButton::JoystickType::SECONDARY, NEW_JOYSTICK ? RobotButton::ControlTypes::AXIS : RobotButton::ControlTypes::KEY, JOYSTICK_TRIGGER_LEFT)),
                manualFireButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUMPER_RIGHT)),
                manualRetractButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUMPER_LEFT)),
                manualOnButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_BACK)),
                speedUpButton(new RobotButton(RobotButton::JoystickType::SECONDARY, NEW_JOYSTICK ? RobotButton::ControlTypes::AXIS : RobotButton::ControlTypes::KEY, JOYSTICK_TRIGGER_RIGHT)),
                speedDownButton(new RobotButton(RobotButton::JoystickType::SECONDARY, NEW_JOYSTICK ? RobotButton::ControlTypes::AXIS : RobotButton::ControlTypes::KEY, JOYSTICK_TRIGGER_LEFT)),
                manualOffButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUTTON_LEFT)),
                state(ShooterState::NONE)
        {
            talon1->SetControlMode(CANTalon::ControlMode::kSpeed);
            talon1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            talon1->SetVoltageRampRate(32.0f);
            talon1->Enable();

            talon2->SetControlMode(CANTalon::ControlMode::kFollower); // kSpeed);
            // talon2->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            talon2->SetVoltageRampRate(32.0f);
            talon2->Enable();
            talon2->Set(7);
        }

        virtual ~Shooter()
        {
        }

        void Update(const bool& teleop);
        void Dashboard();

        void SetState(ShooterState shooterState);
        void AutoShoot();

        bool IsActivated();
};*/
