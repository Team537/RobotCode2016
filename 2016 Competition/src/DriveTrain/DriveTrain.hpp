#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include <Schematic.hpp>
#include <Toolbox/RobotButton.hpp>
#include <Toolbox/TakeBackHalf.hpp>
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
        CANTalon *rightDriveMaster, *rightDriveSlave1, *rightDriveSlave2;
        CANTalon *leftDriveMaster, *leftDriveSlave1, *leftDriveSlave2;

        Solenoid *shifter;
        AHRS *gyro;
        Vision* vision;

        DrivePIDSource *visionPIDSource;
        DrivePIDOutput *visionPIDOutput;
        PIDController *visionPID;

        TakeBackHalf *angleTBH;

        Timer *crossTime;
        bool hasCrossed;
        int crossState;
        bool isClimbing;

        RobotButton *shiftHigh, *shiftLow, *stateUntoggle, *autoCrossToggle;

        float leftSpeedCurrent;
        float rightSpeedCurrent;

        int targetDistance;
        bool crossReverse;

    public:
        enum DriveState
        {
            AUTO_ANGLE, AUTO_DISTANCE, CROSSING, TELEOP_CONTROL, TELEOP_SHOOT, NONE
        };

        DriveState state;

        DriveTrain(Joystick* joystickPrimary, Joystick* joystickSecondary, AHRS *ahrs, Vision* visionTracking) :
                IComponent(joystickPrimary, joystickSecondary, new string("DriveTrain"))
        {
            // Right Master.
            rightDriveMaster = new CANTalon(1);
            rightDriveMaster->SetControlMode(CANTalon::ControlMode::kPosition);
            rightDriveMaster->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            rightDriveMaster->Enable();

            // Right Slave.
            rightDriveSlave1 = new CANTalon(2);
            rightDriveSlave1->SetControlMode(CANTalon::ControlMode::kFollower);
            rightDriveSlave1->Set(1);
            rightDriveSlave1->Enable();

            // Right Slave.
            rightDriveSlave2 = new CANTalon(3);
            rightDriveSlave2->SetControlMode(CANTalon::ControlMode::kFollower);
            rightDriveSlave2->Set(1);
            rightDriveSlave2->Enable();

            // Left Master.
            leftDriveMaster = new CANTalon(4);
            leftDriveMaster->SetControlMode(CANTalon::ControlMode::kPosition);
            leftDriveMaster->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);

            // Left Slave.
            leftDriveSlave1 = new CANTalon(5);
            leftDriveSlave1->SetControlMode(CANTalon::ControlMode::kFollower);
            leftDriveSlave1->Set(4);
            leftDriveSlave1->Enable();

            // Left Slave.
            leftDriveSlave2 = new CANTalon(6);
            leftDriveSlave2->SetControlMode(CANTalon::ControlMode::kFollower);
            leftDriveSlave2->Set(4);
            leftDriveSlave2->Enable();

            // Other robot objects.
            shifter = new Solenoid(4);
            gyro = ahrs;
            vision = visionTracking;

            // Vision angle pids.
            visionPIDSource = new DrivePIDSource();
            visionPIDOutput = new DrivePIDOutput();
            visionPID = new PIDController(0.70f, 0, 0, visionPIDSource, visionPIDOutput);
            visionPID->SetInputRange(-1, 1);
            visionPID->SetOutputRange(-1, 1);
            visionPID->SetContinuous(true);
            // visionPID->SetAbsoluteTolerance(0.05);
            visionPID->Disable();

            angleTBH = new TakeBackHalf(1.75f, -180.0f, 180.0f);

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
            // Secondary: POV 0 = forward cross, 180 = backwards cross.

            // Sets up the state;
            SetState(DriveState::NONE);

            // Initial drive speeds.
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
        float GetCurrentDraw();
};

#endif
