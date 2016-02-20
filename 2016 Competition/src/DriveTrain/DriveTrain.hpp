#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include <Schematic.hpp>
#include <Toolbox/RobotButton.hpp>
#include <Vision/Vision.hpp>

class DriveTrain: public IComponent
{
    private:
        CANTalon *rightDriveMaster, *rightDriveSlave1, *rightDriveSlave2;
        CANTalon *leftDriveMaster, *leftDriveSlave1, *leftDriveSlave2;

        Solenoid *shifter;
        AHRS *gyro;

        Vision* vision;

        RobotButton *shiftHigh, *shiftLow, *rockWallToggle, *roughTerrainToggle, *driveStateUntoggle, *autoCrossToggle;

        Timer *crossTime;
        bool hasCrossed;
        int crossState;

        float leftSpeedCurrent;
        float rightSpeedCurrent;

        int driveDistance;

    public:
        enum DriveState
        {
            AUTO_ANGLE, AUTO_DISTANCE, CROSSING, TELEOP_CONTROL, TELEOP_SHOOT, NONE
        };

        DriveState state;

        DriveTrain(Joystick *joystick, AHRS *ahrs, Vision* visionTracking) :
                IComponent(joystick, new string("DriveTrain"))
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
            crossTime = new Timer;

            // Teleop controls.
            shiftLow = new RobotButton(joystick, JOYSTICK_BUMPER_LEFT);
            shiftHigh = new RobotButton(joystick, JOYSTICK_BUMPER_RIGHT);
            rockWallToggle = new RobotButton(joystick, JOYSTICK_AXIS_BUTTON_RIGHT);
            roughTerrainToggle = new RobotButton(joystick, JOYSTICK_AXIS_BUTTON_LEFT);
            driveStateUntoggle = new RobotButton(joystick, JOYSTICK_TRIGGER_LEFT);
            autoCrossToggle = new RobotButton(joystick, JOYSTICK_X);

            // Sets up the state;
            SetState(DriveState::NONE);

            // Initial drive speeds.
            leftSpeedCurrent = 0;
            rightSpeedCurrent = 0;
            driveDistance = 0;
            crossState = 0;
            hasCrossed = false;
        }

        void Update(bool teleop);
        void Dashboard();

        void SetState(DriveState driveState);

        void Shift(bool highGear);

        void AutoAngle(float angleDegrees);
        void AutoDistance(int distanceIn);
        void Cross();
        bool DefenceCross();

        bool IsWaiting();
        bool IsAtAngle();
        bool IsAtDistance();
        bool HasCrossed();
        float GetCurrentDraw();
};

#endif
