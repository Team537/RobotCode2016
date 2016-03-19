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

        Climber() :
                IComponent(new string("Climber")),
                deployStage1Right(new DigitalInput(0)),
                deployStage2Right(new DigitalInput(1)),
                deployStage1Left(new DigitalInput(2)),
                deployStage2Left(new DigitalInput(3)),
                deployStage1(new Solenoid(2)),
                deployStage2(new Solenoid(3)),
                hooksStage3(new Solenoid(0)),
                gotoNoneButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_BACK)),
                toggleClimbMode(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_START)),
                retractButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_Y)),
                deployHalfButton(new RobotButton(RobotButton::JoystickType::SECONDARY, NEW_JOYSTICK ? RobotButton::ControlTypes::AXIS : RobotButton::ControlTypes::KEY, JOYSTICK_TRIGGER_RIGHT)),
                deployFullButton(new RobotButton(RobotButton::JoystickType::SECONDARY, NEW_JOYSTICK ? RobotButton::ControlTypes::AXIS : RobotButton::ControlTypes::KEY, JOYSTICK_TRIGGER_LEFT)),
                deployHooksButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUMPER_RIGHT)),
                pullUpButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUMPER_LEFT)),
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
