#ifndef SHOOTER_HPP
#define SHOOTER_HPP

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

        RobotButton *gotoNoneButton0, *autoShootButton, *manualAimButton, *manualFireButton, *manualRetractButton, *manualOnButton, *speedUpButton, *speedDownButton, *manualOffButton;

    public:
        enum ShooterState
        {
            NONE, AIMING, SPINNING, FIRE, MANUAL
        };

        ShooterState state;

        Shooter(Joystick* joystickPrimary, Joystick* joystickSecondary, Vision *vision, DriveTrain *drive) :
                IComponent(joystickPrimary, joystickSecondary, new string("Shooter"))
        {
            this->vision = vision;
            this->drive = drive;

            talon1 = new CANTalon(7);
            talon1->SetControlMode(CANTalon::ControlMode::kSpeed);
            talon1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            talon1->SetVoltageRampRate(32.0f);
            talon1->Enable();

            talon2 = new CANTalon(8);
            talon2->SetControlMode(CANTalon::ControlMode::kFollower);//kSpeed);
            //talon2->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            talon2->SetVoltageRampRate(32.0f);
            talon2->Enable();
            talon2->Set(7);

            extendSolenoid = new Solenoid(1);

            extendTimer = new Timer();
            state = ShooterState::NONE;
            spinSpeed = 50.0f;
            manualSpeed = 1.0f;
            autoAdvance = false;

            gotoNoneButton0 = new RobotButton(joystickPrimary, JOYSTICK_BACK, false);
            manualOnButton = new RobotButton(joystickSecondary, JOYSTICK_BACK, false);
            manualOffButton = new RobotButton(joystickSecondary, JOYSTICK_BUTTON_LEFT, false);
            manualFireButton = new RobotButton(joystickSecondary, JOYSTICK_BUMPER_RIGHT, false);
            manualRetractButton = new RobotButton(joystickSecondary, JOYSTICK_BUMPER_LEFT, false);

#if NEW_JOYSTICK
            autoShootButton = new RobotButton(joystickPrimary, JOYSTICK_AXIS_TRIGGER_LEFT, true);
            manualAimButton = new RobotButton(joystickSecondary, JOYSTICK_AXIS_TRIGGER_LEFT, true);
            speedUpButton = new RobotButton(joystickSecondary, JOYSTICK_AXIS_TRIGGER_RIGHT, true);
            speedDownButton = new RobotButton(joystickSecondary, JOYSTICK_AXIS_TRIGGER_LEFT, true);
#else
            autoShootButton = new RobotButton(joystickPrimary, JOYSTICK_TRIGGER_LEFT, false);
            manualAimButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_LEFT, false);
            speedUpButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_RIGHT, false);
            speedDownButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_LEFT, false);

#endif
        }

        void Update(bool teleop);
        void Dashboard();

        void SetState(ShooterState shooterState);
        void AutoShoot();

        bool IsActivated();
};

#endif
