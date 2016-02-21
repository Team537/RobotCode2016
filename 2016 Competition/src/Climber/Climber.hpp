#ifndef CLIMBER_HPP
#define CLIMBER_HPP

#include <Schematic.hpp>
#include <Toolbox/RobotButton.hpp>

class Climber: public IComponent
{
    private:
        DigitalInput *deployStage1Right, *deployStage2Right, *deployStage1Left, *deployStage2Left, *extendLeft, *extendRight;
        Solenoid *deployStage1, *deployStage2, *extendStage3;

        RobotButton *toggleClimbMode, *retractButton, *deployHalfButton, *deployFullButton, *pullUpButton;

        Timer *timer;
        bool climbing;

    public:
        enum ClimberState
        {
            NONE, RETRACT, EXTEND_HALF, EXTEND_FULL, PULL_UP
        };

        ClimberState state;
        ClimberState targetState;

        Climber(Joystick* joystickPrimary, Joystick* joystickSecondary) :
                IComponent(joystickPrimary, joystickSecondary, new string("Climber"))
        {
            deployStage1Right = new DigitalInput(0);
            deployStage2Right = new DigitalInput(1);
            deployStage1Left = new DigitalInput(2);
            deployStage2Left = new DigitalInput(3);
            extendLeft = new DigitalInput(4);
            extendRight = new DigitalInput(5);

            deployStage1 = new Solenoid(2);
            deployStage2 = new Solenoid(3);
            extendStage3 = new Solenoid(4);

            toggleClimbMode = new RobotButton(joystickSecondary, JOYSTICK_START);
            retractButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_LEFT);
            deployHalfButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_RIGHT);
            deployFullButton = new RobotButton(joystickSecondary, JOYSTICK_Y);
            pullUpButton = new RobotButton(joystickSecondary, JOYSTICK_A);

            timer = new Timer();
            climbing = false;

            state = ClimberState::RETRACT;
            targetState = ClimberState::RETRACT;
        }

        void Update(bool teleop);
        void Dashboard();

        void ToggleStage1(bool extend);
        void ToggleStage2(bool extend);
        void ToggleExtend(bool extend);

        bool IsClimbing();
};

#endif
