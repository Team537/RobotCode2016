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

        RobotButton *gotoNoneButton0, *gotoNoneButton1, *autoShootButton, *manualAimButton, *manualFireButton, *flywheelButton, *speedUpButton, *speedDownButton;

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
            manualSpeed = 50.0f;
            autoAdvance = false;

            gotoNoneButton0 = new RobotButton(joystickPrimary, JOYSTICK_BACK);
            gotoNoneButton1 = new RobotButton(joystickSecondary, JOYSTICK_BACK);

#if NEW_JOYSTICK
            autoShootButton = NULL;
            manualAimButton = NULL;
            manualFireButton = NULL;
            flywheelButton = NULL;
#else
            autoShootButton = new RobotButton(joystickPrimary, JOYSTICK_TRIGGER_LEFT);
            manualAimButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_LEFT);
            manualFireButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_RIGHT);
            flywheelButton = new RobotButton(joystickSecondary, JOYSTICK_BACK);
            speedUpButton = new RobotButton(joystickSecondary, JOYSTICK_BUMPER_RIGHT);
            speedDownButton = new RobotButton(joystickSecondary, JOYSTICK_BUMPER_LEFT);

#endif
        }

        void Update(bool teleop);
        void Dashboard();

        void SetState(ShooterState shooterState);
        void AutoShoot();

        bool IsActivated();
};

#endif
