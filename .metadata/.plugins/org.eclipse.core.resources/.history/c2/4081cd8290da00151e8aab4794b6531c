#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

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
        AHRS *gyro;
        Vision* vision;

        DrivePIDSource *visionPIDSource;
        DrivePIDOutput *visionPIDOutput;
        PIDController *visionPID;

        ErrorTimeCubed *angleETC;

        Timer *crossTime;bool hasCrossed;
        int crossState;bool isClimbing;

        RobotButton *shiftHigh, *shiftLow, *stateUntoggle, *autoCrossToggle;

        float crossSpeedMultiplier;bool crossingForward;

        float leftSpeedCurrent;
        float rightSpeedCurrent;

        int targetDistance;bool crossReverse;

    public:
        enum DriveState
        {
            AUTO_ANGLE, AUTO_DISTANCE, CROSSING, TELEOP_CONTROL, TELEOP_SHOOT, NONE
        };

        DriveState state;

        DriveTrain(Joystick* joystickPrimary, Joystick* joystickSecondary, AHRS *ahrs, Vision* visionTracking) :
                IComponent(joystickPrimary, joystickSecondary, new string("DriveTrain"))
        {
            // Left Master.
            leftDriveMaster = new CANTalon(1);
            leftDriveMaster->SetControlMode(CANTalon::ControlMode::kPosition);
            leftDriveMaster->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);

            // Left Slave.
            leftDriveSlave1 = new CANTalon(3);
            leftDriveSlave1->SetControlMode(CANTalon::ControlMode::kFollower);
            leftDriveSlave1->Set(1);
            leftDriveSlave1->Enable();

            // Left Slave.
            leftDriveSlave2 = new CANTalon(5);
            leftDriveSlave2->SetControlMode(CANTalon::ControlMode::kFollower);
            leftDriveSlave2->Set(1);
            leftDriveSlave2->Enable();

            // Right Master.
            rightDriveMaster = new CANTalon(2);
            rightDriveMaster->SetControlMode(CANTalon::ControlMode::kPosition);
            rightDriveMaster->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            rightDriveMaster->Enable();

            // Right Slave.
            rightDriveSlave1 = new CANTalon(4);
            rightDriveSlave1->SetControlMode(CANTalon::ControlMode::kFollower);
            rightDriveSlave1->Set(2);
            rightDriveSlave1->Enable();

            // Right Slave.
            rightDriveSlave2 = new CANTalon(6);
            rightDriveSlave2->SetControlMode(CANTalon::ControlMode::kFollower);
            rightDriveSlave2->Set(2);
            rightDriveSlave2->Enable();

            // Other robot objects.
            shift = new Solenoid(0);
            gyro = ahrs;
            vision = visionTracking;

            // Vision angle pids.
            visionPIDSource = new DrivePIDSource();
            visionPIDOutput = new DrivePIDOutput();
            visionPID = new PIDController(0.70f, 0, 0, visionPIDSource, visionPIDOutput);
            visionPID->SetInputRange(-1, 1);
            visionPID->SetOutputRange(-1, 1);
            visionPID->SetContinuous(true);
            visionPID->SetAbsoluteTolerance(0.05);
            visionPID->Disable();

            // Angle ETC.
            angleETC = new ErrorTimeCubed(1.75f, 45.0f, -180.0f, 180.0f);

            // Crossing timers.
            crossTime = new Timer();
            hasCrossed = false;
            crossState = 0;
            isClimbing = true;

            // Teleop controls.
            shiftLow = new RobotButton(joystickPrimary, JOYSTICK_BUMPER_LEFT);
            shiftHigh = new RobotButton(joystickPrimary, JOYSTICK_BUMPER_RIGHT);
            stateUntoggle = new RobotButton(joystickPrimary, JOYSTICK_BACK);
            autoCrossToggle = new RobotButton(joystickPrimary, JOYSTICK_TRIGGER_RIGHT);

            // Sets up the state;
            SetState(DriveState::NONE);

            // Initial drive speeds.
            crossSpeedMultiplier = 1.0f;
            crossingForward = true;

            leftSpeedCurrent = 0;
            rightSpeedCurrent = 0;
            targetDistance = 0;
            crossReverse = false;
        }

        void Update(bool teleop);
        bool DefenceCross();
        void Dashboard();

        void SetState(DriveState driveState);
        void Shift(bool highGear);

        void AutoAngle(float angleDegrees);
        void AutoDistance(int distanceIn);
        void Cross(bool reverse);
        void SetCrossing(bool crossing);

        bool IsWaiting();
        bool IsTeleopControl();
        float GetCurrentDraw();
};

#endif
