#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include <Schematic.hpp>
#include <Toolbox/RobotButton.hpp>
#include <Vision/Vision.hpp>

class DriveTrain: public IComponent
{
    private:
        CANTalon *rightDrive1, *rightDrive2, *rightDrive3;
        CANTalon *leftDrive4, *leftDrive5, *leftDrive6;

        Solenoid *shifter;
        AHRS *gyro;

        Vision* vision;

        RobotButton *shiftHigh, *shiftLow, *rockWallToggle, *roughTerrainToggle;

        float leftSpeedCurrent;
        float rightSpeedCurrent;
        float leftSpeedOld;
        float rightSpeedOld;
        float leftSpeedDelta;
        float rightSpeedDelta;
        float leftDriveSign;
        float rightDriveSign;

    public:
        enum DriveState
        {
            AUTO_ANGLE, AUTO_DISTANCE, TELEOP_CONTROL, TELEOP_SHOOT, NONE
        };

        DriveState state;

        DriveTrain(Joystick *joystick, AHRS *ahrs, Vision* visionTracking) :
                IComponent(joystick, new string("DriveTrain"))
        {
            // Right Master.
            rightDrive1 = new CANTalon(1);
            rightDrive1->SetControlMode(CANTalon::ControlMode::kPercentVbus);
            rightDrive1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);

            // Right Slave.
            rightDrive2 = new CANTalon(2);
            rightDrive2->SetControlMode(CANTalon::ControlMode::kFollower);
            rightDrive2->Set(1);

            // Right Slave.
            rightDrive3 = new CANTalon(3);
            rightDrive3->SetControlMode(CANTalon::ControlMode::kFollower);
            rightDrive3->Set(1);

            // Left Master.
            leftDrive4 = new CANTalon(4);
            leftDrive4->SetControlMode(CANTalon::ControlMode::kPercentVbus);
            leftDrive4->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);

            // Left Slave.
            leftDrive5 = new CANTalon(5);
            leftDrive5->SetControlMode(CANTalon::ControlMode::kFollower);
            leftDrive5->Set(4);

            // Left Slave.
            leftDrive6 = new CANTalon(6);
            leftDrive6->SetControlMode(CANTalon::ControlMode::kFollower);
            leftDrive6->Set(4);

            // Other robot objects.
            shifter = new Solenoid(4);
            gyro = ahrs;
            vision = visionTracking;

            // Teleop controls.
            shiftLow = new RobotButton(joystick, JOYSTICK_BUMPER_LEFT);
            shiftHigh = new RobotButton(joystick, JOYSTICK_BUMPER_RIGHT);
            rockWallToggle = new RobotButton(joystick, JOYSTICK_AXIS_BUTTON_RIGHT);
            roughTerrainToggle = new RobotButton(joystick, JOYSTICK_AXIS_BUTTON_LEFT);

            // Sets up the state;
            SetState(DriveState::NONE);

            // Initial drive speeds.
            leftSpeedCurrent = 0;
            rightSpeedCurrent = 0;
            leftSpeedOld = 0;
            rightSpeedOld = 0;
            leftSpeedDelta = 0;
            rightSpeedDelta = 0;
            leftDriveSign = 1;
            rightDriveSign = 1;
        }

        void Update(bool teleop);
        void Dashboard();

        void SetState(DriveState driveState);

        void Shift(bool highGear);

        void AutoAngle(float angleDegrees);
        void AutoDistance(float distanceFt);

        bool IsWaiting();bool IsAtAngle();bool IsAtDistance();
        float GetCurrentDraw();
};

#endif
