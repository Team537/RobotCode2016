#ifndef CLIMBER_HPP
#define CLIMBER_HPP

#include <Schematic.hpp>
#include <Toolbox/RobotButton.hpp>

class Climber: public IComponent
{
    private:
        DigitalInput *deployStage1Right, *deployStage2Right, *deployStage1Left, *deployStage2Left, *extendLeft, *extendRight;
        Solenoid *deployStage1, *deployStage2, *extendStage3;

        RobotButton *gotoNoneButton, *toggleClimbMode, *retractButton, *deployHalfButton, *deployFullButton, *deployHooksButton, *pullUpButton;

        Timer *timer;
        bool climbing;
        string stateNames[6] = {"None", "Retract", "Extend Half", "Extend Full", "Extend Hooks", "Pull Up"};

    public:
        enum ClimberState
        {
            NONE, RETRACT, EXTEND_HALF, EXTEND_FULL, EXTEND_HOOKS, PULL_UP
        };

        ClimberState state;

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

            gotoNoneButton = new RobotButton(joystickSecondary, JOYSTICK_BACK);

#if NEW_JOYSTICK
            retractButton = NULL;
            deployHalfButton = NULL;
#else
            retractButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_LEFT);
            deployHalfButton = new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_RIGHT);
#endif

            deployFullButton = new RobotButton(joystickSecondary, JOYSTICK_Y);
            deployHooksButton = new RobotButton(joystickSecondary, JOYSTICK_X);
            pullUpButton = new RobotButton(joystickSecondary, JOYSTICK_A);

            timer = new Timer();
            climbing = false;

            state = ClimberState::RETRACT;
        }

        void Update(bool teleop);
        void Dashboard();

        void ToggleStage1(bool extend);
        void ToggleStage2(bool extend);
        void ToggleExtend(bool extend);

        bool IsClimbing();
};

#endif
