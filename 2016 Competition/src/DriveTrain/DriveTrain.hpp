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

        RobotButton *shiftHigh, *shiftLow, *rockWallToggle, *roughTerrainToggle, *distUntoggle, *distanceToggle;

        float leftSpeedCurrent;
        float rightSpeedCurrent;

        int driveDistance = 0;

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
            rightDrive1->SetControlMode(CANTalon::ControlMode::kPosition);//kPercentVbus);
            rightDrive1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            rightDrive1->SetPID(0.085f, 0.0f, 0.0f);
            rightDrive1->SetVoltageRampRate(24.0f);
            rightDrive1->Enable();

            // Right Slave.
            rightDrive2 = new CANTalon(2);
            rightDrive2->SetControlMode(CANTalon::ControlMode::kFollower);
            rightDrive2->Set(1);
            rightDrive2->Enable();

            // Right Slave.
            rightDrive3 = new CANTalon(3);
            rightDrive3->SetControlMode(CANTalon::ControlMode::kFollower);
            rightDrive3->Set(1);
            rightDrive3->Enable();

            // Left Master.
            leftDrive4 = new CANTalon(4);
            leftDrive4->SetControlMode(CANTalon::ControlMode::kPosition);//kPercentVbus);
            leftDrive4->SetPID(0.085f, 0.0f, 0.0f);
            leftDrive4->SetVoltageRampRate(24.0f);
            leftDrive4->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);

            // Left Slave.
            leftDrive5 = new CANTalon(5);
            leftDrive5->SetControlMode(CANTalon::ControlMode::kFollower);
            leftDrive5->Set(4);
            leftDrive5->Enable();

            // Left Slave.
            leftDrive6 = new CANTalon(6);
            leftDrive6->SetControlMode(CANTalon::ControlMode::kFollower);
            leftDrive6->Set(4);
            leftDrive6->Enable();

            // Other robot objects.
            shifter = new Solenoid(4);
            gyro = ahrs;
            vision = visionTracking;

            // Teleop controls.
            shiftLow = new RobotButton(joystick, JOYSTICK_BUMPER_LEFT);
            shiftHigh = new RobotButton(joystick, JOYSTICK_BUMPER_RIGHT);
            rockWallToggle = new RobotButton(joystick, JOYSTICK_AXIS_BUTTON_RIGHT);
            roughTerrainToggle = new RobotButton(joystick, JOYSTICK_AXIS_BUTTON_LEFT);
            distUntoggle = new RobotButton(joystick, JOYSTICK_TRIGGER_LEFT);
            distanceToggle = new RobotButton(joystick, JOYSTICK_TRIGGER_RIGHT);

            // Sets up the state;
            SetState(DriveState::NONE);

            // Initial drive speeds.
            leftSpeedCurrent = 0;
            rightSpeedCurrent = 0;
        }

        void Update(bool teleop);
        void Dashboard();

        void SetState(DriveState driveState);

        void Shift(bool highGear);

        void AutoAngle(float angleDegrees);
        void AutoDistance(int distanceIn);

        bool IsWaiting();
        bool IsAtAngle();
        bool IsAtDistance();
        float GetCurrentDraw();
};

#endif
