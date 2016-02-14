#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include <DriveTrain/PIDAngleOutput.hpp>
#include <Schematic.hpp>
#include <DriveTrain/PIDAngleSource.hpp>
#include <Toolbox/RobotButton.hpp>
#include <Vision/Vision.hpp>

class DriveTrain: public IComponent
{
private:
	CANTalon *rightDrive1, *rightDrive2, *rightDrive3;
	CANTalon *leftDrive4, *leftDrive5, *leftDrive6;

	RobotButton *shiftHigh, *shiftLow, *rockWallToggle, *roughTerrainToggle, *shootButton;

	Solenoid *shifter;
	AHRS *ahrs;

	Vision* vision;

	PIDController *PIDDriveDistance;

	PIDAngleSource *anglePIDSource;
	PIDAngleOutput *anglePIDOutput;
	PIDController *anglePID;

	float encoderGoal;
	float targetAngle;

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
		NONE, GOTO_ANGLE, GOTO_DISTANCE, TELE_SHOOTER, TELE_CONTROL
	};

	DriveState state;

	DriveTrain(Joystick *joystick, AHRS *ahrs, Vision* visionTracking) : IComponent(joystick, new string("DriveTrain"))
	{
		rightDrive1 = new CANTalon(1);
		rightDrive1->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		rightDrive1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);

		rightDrive2 = new CANTalon(2);
		rightDrive2->SetControlMode(CANTalon::ControlMode::kFollower);
		rightDrive2->Set(1);

		rightDrive3 = new CANTalon(3);
		rightDrive3->SetControlMode(CANTalon::ControlMode::kFollower);
		rightDrive3->Set(1);

		leftDrive4 = new CANTalon(4);
		leftDrive4->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		leftDrive4->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);

		leftDrive5 = new CANTalon(5);
		leftDrive5->SetControlMode(CANTalon::ControlMode::kFollower);
		leftDrive5->Set(4);

		leftDrive6 = new CANTalon(6);
		leftDrive6->SetControlMode(CANTalon::ControlMode::kFollower);
		leftDrive6->Set(4);

		shiftLow = new RobotButton(joystick, JOYSTICK_BUMPER_LEFT);
		shiftHigh = new RobotButton(joystick, JOYSTICK_BUMPER_RIGHT);
		rockWallToggle = new RobotButton(joystick, JOYSTICK_AXIS_BUTTON_RIGHT);
		roughTerrainToggle = new RobotButton(joystick, JOYSTICK_AXIS_BUTTON_LEFT);
		shootButton = new RobotButton(joystick, JOYSTICK_TRIGGER_RIGHT);

		shifter = new Solenoid(4);
		this->ahrs = ahrs;
		vision = visionTracking;

		PIDDriveDistance = new PIDController(DRIVE_DISTANCE_PID, SpeedEncoder, SpeedOutput);

		anglePIDSource = new PIDAngleSource();
		anglePIDOutput = new PIDAngleOutput();
		anglePID = new PIDController(0.002f, 0, 0, anglePIDSource, anglePIDOutput);
		anglePID->SetInputRange(-1, 1);
		anglePID->SetOutputRange(-1, 1);
		anglePID->SetContinuous(true);
		anglePID->SetAbsoluteTolerance(DRIVE_ANGLE_TOLERENCE);
		anglePID->Disable();

		encoderGoal = 0;
		targetAngle = 0;

		ChangeState(DriveState::NONE);

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

	void ChangeState(DriveState newState);
	void AutoDrive(float distanceFt);
	void AutoAngle(float targetAngle);
	void Shift(bool highGear);

	bool IsEnabled();
	bool IsWaiting();
	bool OnTargetAngle();
	bool OnTargetDistance();
};

#endif
