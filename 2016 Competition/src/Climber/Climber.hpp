#pragma once

#include <Schematic.hpp>
#include <Toolbox/RobotButton.hpp>
#include <Collector/Collector.hpp>

class Climber: public IComponent
{
    private:
        DigitalInput *deployStage1Right, *deployStage2Right, *deployStage1Left, *deployStage2Left;
        Solenoid *deployStage1, *deployStage2, *hooksStage3, *popUp;

        RobotButton *gotoNoneButton, *toggleClimbMode, *toggleFullSpeed, *retractButton, *deployHalfButton, *deployFullButton, *deployHooksButton, *pullUpButton, *noModeHalf;

        Timer *timer;
        bool climbing, deployedFull, fullSpeed;
        string stateNames[6] = {"None", "Retract", "Extend Half", "Extend Full", "Extend Hooks", "Pull Up"};
        Collector *collector;

    public:
        enum ClimberState
        {
            NONE, RETRACT, EXTEND_HALF, EXTEND_FULL, EXTEND_HOOKS, PULL_UP
        };
        enum HookState
        {
            EXTENDED, RETRACTED
        };

        ClimberState state;
        ClimberState lastState;
        HookState hookState;

        Climber() :
                IComponent(new string("Climber")),
                deployStage1Right(new DigitalInput(0)),
                deployStage2Right(new DigitalInput(1)),
                deployStage1Left(new DigitalInput(2)),
                deployStage2Left(new DigitalInput(3)),
                deployStage1(new Solenoid(2)),
                deployStage2(new Solenoid(3)),
                hooksStage3(new Solenoid(0)),
                popUp(new Solenoid(1)),
                gotoNoneButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_BACK)),
                toggleClimbMode(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_START)),
                retractButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_Y)),
                deployHalfButton(new RobotButton(RobotButton::JoystickType::SECONDARY, NEW_JOYSTICK ? RobotButton::ControlTypes::AXIS : RobotButton::ControlTypes::KEY, JOYSTICK_TRIGGER_RIGHT)),
                deployFullButton(new RobotButton(RobotButton::JoystickType::SECONDARY, NEW_JOYSTICK ? RobotButton::ControlTypes::AXIS : RobotButton::ControlTypes::KEY, JOYSTICK_TRIGGER_LEFT)),
                deployHooksButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUMPER_RIGHT)),
                pullUpButton(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUMPER_LEFT)),
                toggleFullSpeed(new RobotButton(RobotButton::JoystickType::SECONDARY, RobotButton::ControlTypes::KEY, JOYSTICK_X)),
                noModeHalf(new RobotButton(RobotButton::JoystickType::PRIMARY, NEW_JOYSTICK ? RobotButton::ControlTypes::AXIS : RobotButton::ControlTypes::KEY, JOYSTICK_TRIGGER_LEFT)),
                timer(new Timer()),
                climbing(false),
                deployedFull(false),
                fullSpeed(true),
                state(ClimberState::RETRACT),
                hookState(HookState::RETRACTED),
                collector(new Collector)
        {
        }

        virtual ~Climber()
        {
        }

        void Init();
        void Update(const bool& teleop);
        void SetState(ClimberState state);
        void DeployHooks(HookState hookState);
        void UpdatePopUp();
        void Dashboard();

        void ToggleStage1(const bool& extend);
        void ToggleStage2(const bool& extend);
        void ToggleExtend(const bool& extend);
        void TogglePopup(const bool& up);
        inline bool IsClimbing() const { return climbing; }
        inline bool IsFullSpeed() const { return fullSpeed; }
        inline int ReturnState() {return state;}
};
