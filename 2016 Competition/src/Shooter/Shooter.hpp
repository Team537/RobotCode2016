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

        CANTalon *spinTalon;
        Solenoid *extend;

        Timer *extendTimer;

        RobotButton *aimButton, *shootButton;
        float spinSpeed;

    public:
        enum ShooterState
        {
            NONE, AIMING_SPINNING, FIRE, RETRACT
        };

        ShooterState state;

        Shooter(Joystick *joystick, Vision *vision, DriveTrain *drive) :
                IComponent(joystick, new string("Shooter"))
        {
            this->vision = vision;
            this->drive = drive;

            spinTalon = new CANTalon(9);
            extend = new Solenoid(5);

            extendTimer = new Timer();

            state = ShooterState::NONE;
            aimButton = new RobotButton(joystick, JOYSTICK_TRIGGER_LEFT);
            shootButton = new RobotButton(joystick, JOYSTICK_TRIGGER_RIGHT);
            spinSpeed = 0.0f;
        }

        void Update(bool teleop);
        void Dashboard();

        bool IsActivated();
};

#endif
