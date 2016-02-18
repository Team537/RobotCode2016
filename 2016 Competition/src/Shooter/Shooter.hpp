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

        CANTalon *spinTalon1, *spinTalon2;
        Solenoid *extendSolenoid;

        Timer *extendTimer;

        RobotButton *shootButton;
        float spinSpeed;

    public:
        enum ShooterState
        {
            NONE, AIMING_SPINNING, FIRE
        };

        ShooterState state;

        Shooter(Joystick *joystick, Vision *vision, DriveTrain *drive) :
                IComponent(joystick, new string("Shooter"))
        {
            this->vision = vision;
            this->drive = drive;

            spinTalon1 = new CANTalon(8);
            spinTalon1->SetControlMode(CANTalon::ControlMode::kPercentVbus);
            spinTalon1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            spinTalon1->Enable();

            spinTalon2 = new CANTalon(9);
            spinTalon2->SetControlMode(CANTalon::ControlMode::kFollower);
            spinTalon2->Set(8);
            spinTalon2->Enable();

            extendSolenoid = new Solenoid(5);

            extendTimer = new Timer();

            state = ShooterState::NONE;

            shootButton = new RobotButton(joystick, JOYSTICK_TRIGGER_RIGHT);
            spinSpeed = 0.0f;
        }

        void Update(bool teleop);
        void Dashboard();

        bool IsActivated();
};

#endif
