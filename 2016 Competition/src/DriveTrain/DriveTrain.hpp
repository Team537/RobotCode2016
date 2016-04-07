#pragma once

#include <Schematic.hpp>
#include <Toolbox/ErrorTimeCubed.hpp>
#include <Toolbox/RobotButton.hpp>
#include <Vision/Vision.hpp>

class DrivePIDSource: public PIDSource
{
    private:
        double target;
    public:
        DrivePIDSource()
        {
            target = -1;
        }

        virtual ~DrivePIDSource()
        {
        }

        void SetPIDSourceType(PIDSourceType pidSource)
        {
            m_pidSource = pidSource;
        }

        void SetPIDTarget(double center)
        {
            target = center;
        }

        double PIDGet()
        {
            return target;
        }
};

class DrivePIDOutput: public PIDOutput
{
    private:
        float output;
    public:
        DrivePIDOutput()
        {
            output = 0;
        }

        virtual ~DrivePIDOutput()
        {
        }

        void PIDWrite(float output)
        {
            this->output = output;
        }

        float GetOutput()
        {
            return output;
        }
};

class DriveTrain: public IComponent
{
    private:
        CANTalon *leftDriveMaster, *leftDriveSlave1, *leftDriveSlave2;
        CANTalon *rightDriveMaster, *rightDriveSlave1, *rightDriveSlave2;

        Solenoid *shift;
        Vision* vision;

        DrivePIDSource *visionPIDSource;
        DrivePIDOutput *visionPIDOutput;
        PIDController *visionPID;

        ErrorTimeCubed *angleETC;

        Timer *crossTime;
        bool hasCrossed;
        int crossState;
        bool isClimbing;
        bool climbingFullSpeed;

        Timer *driveTime;
        int timedDriveState;

        RobotButton *shiftHigh, *shiftLow, *stateUntoggle, *autoCrossToggle, *reverseToggle;

        float crossSpeedMultiplier;
        bool crossingForward;

        float leftSpeedCurrent;
        float rightSpeedCurrent;

        int targetDistance;
        bool crossReverse;
        string stateNames[7] = {"None", "Auto Angle", "Auto Distance", "Crossing", "Teleop Control", "Teleop Shoot", "Auto_Timed"};

        bool reverse;
        bool primaryDriving;

    public:
        enum DriveState
        {
            NONE, AUTO_ANGLE, AUTO_DISTANCE, CROSSING, TELEOP_CONTROL, TELEOP_SHOOT, AUTO_TIMED
        };

        DriveState state;

        DriveTrain(Vision* visionTracking) :
                IComponent(new string("DriveTrain")),
                leftDriveMaster(new CANTalon(1)),
                leftDriveSlave1(new CANTalon(3)),
                leftDriveSlave2(new CANTalon(5)),
                rightDriveMaster(new CANTalon(2)),
                rightDriveSlave1(new CANTalon(4)),
                rightDriveSlave2(new CANTalon(6)),
                shift(new Solenoid(4)),
                vision(visionTracking),
                visionPIDSource(new DrivePIDSource()),
                visionPIDOutput(new DrivePIDOutput()),
                visionPID(new PIDController(0.70f, 0, 0, visionPIDSource, visionPIDOutput)),
                angleETC(new ErrorTimeCubed(DRIVE_ANGLE_TOLERANCE, 45.0f, -180.0f, 180.0f)),
                crossTime(new Timer()),
                hasCrossed(false),
                crossState(0),
                isClimbing(true),
                driveTime(new Timer()),
                timedDriveState(0),
                shiftHigh(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUMPER_RIGHT)),
                shiftLow(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_BUMPER_LEFT)),
                stateUntoggle(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_BACK)),
                autoCrossToggle(new RobotButton(RobotButton::JoystickType::PRIMARY, NEW_JOYSTICK ? RobotButton::ControlTypes::AXIS : RobotButton::ControlTypes::KEY, JOYSTICK_TRIGGER_RIGHT)),
                reverseToggle(new RobotButton(RobotButton::JoystickType::PRIMARY, RobotButton::ControlTypes::KEY, JOYSTICK_X)),
                crossSpeedMultiplier(1.0f),
                crossingForward(true),
                leftSpeedCurrent(0),
                rightSpeedCurrent(0),
                targetDistance(0),
                crossReverse(false),
                reverse(true),
                primaryDriving(false),
                state(DriveState::NONE)
        {
            leftDriveMaster->SetControlMode(CANTalon::ControlMode::kPosition);
            leftDriveMaster->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);

            leftDriveSlave1->SetControlMode(CANTalon::ControlMode::kFollower);
            leftDriveSlave1->Enable();
            leftDriveSlave1->Set(1);

            leftDriveSlave2->SetControlMode(CANTalon::ControlMode::kFollower);
            leftDriveSlave2->Enable();
            leftDriveSlave2->Set(1);

            rightDriveMaster->SetControlMode(CANTalon::ControlMode::kPosition);
            rightDriveMaster->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            rightDriveMaster->Enable();

            rightDriveSlave1->SetControlMode(CANTalon::ControlMode::kFollower);
            rightDriveSlave1->Enable();
            rightDriveSlave1->Set(2);

            rightDriveSlave2->SetControlMode(CANTalon::ControlMode::kFollower);
            rightDriveSlave2->Enable();
            rightDriveSlave2->Set(2);

            visionPID->SetInputRange(-1, 1);
            visionPID->SetOutputRange(-1, 1);
            visionPID->SetContinuous(true);
            visionPID->SetAbsoluteTolerance(0.05);
            visionPID->Disable();
        }

        void Update(const bool& teleop);
        bool DefenceCross();
        void Dashboard();

        void SetState(DriveState driveState);
        void Shift(const bool& highGear);

        void AutoAngle(const float& angleDegrees);
        void AutoDistance(const int& distanceIn);
        void AutoTimed();
        void Cross(const bool& reverse, const float& speed);
        void SetClimbing(const bool& climbing);
        void SetClimbingFullSpeed(const bool& fullSpeed);

        bool IsWaiting();
        bool IsTeleopControl();
        float GetCurrentDraw();
};
