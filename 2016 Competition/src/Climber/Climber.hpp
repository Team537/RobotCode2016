#pragma once

#include <Schematic.hpp>
#include <Toolbox/RobotButton.hpp>

class Climber: public IComponent
{
    private:
        DigitalInput *deployStage1Right, *deployStage2Right, *deployStage1Left, *deployStage2Left;
        Solenoid *deployStage1, *deployStage2, *hooksStage3;

        RobotButton *gotoNoneButton, *toggleClimbMode, *retractButton, *deployHalfButton, *deployFullButton, *deployHooksButton, *pullUpButton;

        Timer *timer;
        bool climbing, deployedFull;
        string stateNames[6] = {"None", "Retract", "Extend Half", "Extend Full", "Extend Hooks", "Pull Up"};

    public:
        enum ClimberState
        {
            NONE, RETRACT, EXTEND_HALF, EXTEND_FULL, EXTEND_HOOKS, PULL_UP
        };

        ClimberState state;

        Climber(Joystick* joystickPrimary, Joystick* joystickSecondary) :
                IComponent(joystickPrimary, joystickSecondary, new string("Climber")),
                deployStage1Right(new DigitalInput(0)),
                deployStage2Right(new DigitalInput(1)),
                deployStage1Left(new DigitalInput(2)),
                deployStage2Left(new DigitalInput(3)),
                deployStage1(new Solenoid(2)),
                deployStage2(new Solenoid(3)),
                hooksStage3(new Solenoid(0)),
                gotoNoneButton(new RobotButton(joystickSecondary, JOYSTICK_BACK, false)),
                toggleClimbMode(new RobotButton(joystickSecondary, JOYSTICK_START, false)),
                retractButton(new RobotButton(joystickSecondary, JOYSTICK_Y, false)),
                deployHalfButton(new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_RIGHT, NEW_JOYSTICK)),
                deployFullButton(new RobotButton(joystickSecondary, JOYSTICK_TRIGGER_LEFT, NEW_JOYSTICK)),
                deployHooksButton(new RobotButton(joystickSecondary, JOYSTICK_BUMPER_RIGHT, false)),
                pullUpButton(new RobotButton(joystickSecondary, JOYSTICK_BUMPER_LEFT, false)),
                timer(new Timer()),
                climbing(false),
                deployedFull(false),
                state(ClimberState::RETRACT)
        {
        }

        virtual ~Climber()
        {
        }

        void Init();
        void Update(const bool& teleop);
        void Dashboard();

        void ToggleStage1(const bool& extend);
        void ToggleStage2(const bool& extend);
        void ToggleExtend(const bool& extend);
        inline bool IsClimbing() const { return climbing; }
};
