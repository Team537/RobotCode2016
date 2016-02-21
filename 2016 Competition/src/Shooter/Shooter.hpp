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

        CANTalon *talonMaster, *talonSlave;
        Solenoid *extendSolenoid;

        Timer *extendTimer;
        float spinSpeed;

        RobotButton *autoShootButton, *manualAimButton, *manualShootButton;

    public:
        enum ShooterState
        {
            NONE, AIMING_SPINNING, FIRE
        };

        ShooterState state;

        Shooter(Joystick* joystickPrimary, Joystick* joystickSecondary, Vision *vision, DriveTrain *drive) :
                IComponent(joystickPrimary, joystickSecondary, new string("Shooter"))
        {
            this->vision = vision;
            this->drive = drive;

            talonMaster = new CANTalon(8);
            talonMaster->SetControlMode(CANTalon::ControlMode::kPercentVbus);
            talonMaster->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            talonMaster->Enable();

            talonSlave = new CANTalon(9);
            talonSlave->SetControlMode(CANTalon::ControlMode::kFollower);
            talonSlave->Set(8);
            talonSlave->Enable();

            extendSolenoid = new Solenoid(5);

            extendTimer = new Timer();
            state = ShooterState::NONE;
            spinSpeed = 0.0f;

            autoShootButton = new RobotButton(joystickPrimary, JOYSTICK_TRIGGER_LEFT);
            manualAimButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_LEFT);
            manualShootButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_RIGHT);
        }

        void Update(bool teleop);
        void Dashboard();

        bool IsActivated();
};

#endif