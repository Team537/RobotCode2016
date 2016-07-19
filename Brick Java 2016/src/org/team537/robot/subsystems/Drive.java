package org.team537.robot.subsystems;

import org.team537.robot.RobotMap;
import org.team537.robot.commands.DriveArcade;
import org.team537.robot.commands.DriveTank;
import org.team537.toolbox.Maths;

import edu.wpi.first.wpilibj.CANTalon;
import edu.wpi.first.wpilibj.Solenoid;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Drive extends Subsystem {
	private final CANTalon leftDriveMaster = new CANTalon(RobotMap.CAN.DRIVE_LEFT_0);
	private final CANTalon leftDriveSlave1 = new CANTalon(RobotMap.CAN.DRIVE_LEFT_1);
	private final CANTalon leftDriveSlave2 = new CANTalon(RobotMap.CAN.DRIVE_LEFT_2);

	private final CANTalon rightDriveMaster = new CANTalon(RobotMap.CAN.DRIVE_RIGHT_0);
	private final CANTalon rightDriveSlave1 = new CANTalon(RobotMap.CAN.DRIVE_RIGHT_1);
	private final CANTalon rightDriveSlave2 = new CANTalon(RobotMap.CAN.DRIVE_RIGHT_2);

	private final Solenoid shifter = new Solenoid(RobotMap.Solenoid.DRIVE_SHIFTER);
	
	private boolean fullspeed = false;

	public Drive() {
		leftDriveMaster.setFeedbackDevice(CANTalon.FeedbackDevice.QuadEncoder);
		leftDriveMaster.configEncoderCodesPerRev(1024);

		leftDriveSlave1.changeControlMode(CANTalon.TalonControlMode.Follower);
		leftDriveSlave1.set(RobotMap.CAN.DRIVE_LEFT_0);

		leftDriveSlave2.changeControlMode(CANTalon.TalonControlMode.Follower);
		leftDriveSlave2.set(RobotMap.CAN.DRIVE_LEFT_0);

		rightDriveMaster.setFeedbackDevice(CANTalon.FeedbackDevice.QuadEncoder);
		rightDriveMaster.configEncoderCodesPerRev(1024);

		rightDriveSlave1.changeControlMode(CANTalon.TalonControlMode.Follower);
		rightDriveSlave1.set(RobotMap.CAN.DRIVE_RIGHT_0);

		rightDriveSlave2.changeControlMode(CANTalon.TalonControlMode.Follower);
		rightDriveSlave2.set(RobotMap.CAN.DRIVE_RIGHT_0);
		
		shiftLow();
		stop();
	}

	/**
	 * Updates the subsystems dashboard readings.
	 */
	public void dashboard() {
		SmartDashboard.putString("Drive Gear", shifter.get() ? "High" : "Low");
		SmartDashboard.putBoolean("Drive Fullspeed", fullspeed);

		SmartDashboard.putNumber("Drive Setpoint Left", leftDriveMaster.getSetpoint());
		SmartDashboard.putNumber("Drive Setpoint Right", rightDriveMaster.getSetpoint());

		SmartDashboard.putNumber("Drive Error Left", leftDriveMaster.getClosedLoopError());
		SmartDashboard.putNumber("Drive Error Right", rightDriveMaster.getClosedLoopError());

		SmartDashboard.putNumber("Drive Speed Left", leftDriveMaster.getSpeed());
		SmartDashboard.putNumber("Drive Speed Right", rightDriveMaster.getSpeed());

		SmartDashboard.putNumber("Drive Encoder Pos Left", leftDriveMaster.getEncPosition());
		SmartDashboard.putNumber("Drive Encoder Pos Right", rightDriveMaster.getEncPosition());
	}

	@Override
	protected void initDefaultCommand() {
		if (RobotMap.Driver.ARCADE_DRIVE) {
			setDefaultCommand(new DriveArcade());
		} else {
			setDefaultCommand(new DriveTank());
		}
	}

	/**
	 * Drives the drive train from left and right speeds.
	 * 
	 * @param left The input left speed.
	 * @param right The input right speed.
	 */
	public void driveSpeed(double speedLeft, double speedRight) {
		changeControlMode(CANTalon.TalonControlMode.PercentVbus);
		if (!fullspeed) {
			speedLeft *= RobotMap.Driver.DRIVE_SPEED;
			speedRight *= RobotMap.Driver.DRIVE_SPEED;
		}
		leftDriveMaster.set(Maths.clamp(speedLeft, -1.0, 1.0));
		rightDriveMaster.set(-Maths.clamp(speedRight, -1.0, 1.0));
	}

	/**
	 * Drives the drive train from left and right encoder rates.
	 * 
	 * @param left The input left encoder rate.
	 * @param right The input right encoder rate.
	 */
	public void driveRate(final double left, final double right) {
		changeControlMode(CANTalon.TalonControlMode.Speed);
		leftDriveMaster.set(left);
		rightDriveMaster.set(-right);
	}

	/**
	 * Drives the drive train to a left and right encoder distance.
	 * 
	 * @param left The input left distance (inches).
	 * @param right The input right distance (inches).
	 */
	public void driveDistance(final double left, final double right) {
		changeControlMode(CANTalon.TalonControlMode.Position);
		leftDriveMaster.set(left * RobotMap.Digital.DRIVE_IN_TO_ENCODER);
		rightDriveMaster.set(-right * RobotMap.Digital.DRIVE_IN_TO_ENCODER);
	}

	/**
	 * Drives the drive train to a angle.
	 * 
	 * @param angle The angle to go to (degrees).
	 */
	public void driveAngle(final double angle) {
		changeControlMode(CANTalon.TalonControlMode.PercentVbus);
		// TODO: Drive to angle!
	}

	/**
	 * Changes the current control mode of the drive trains talons.
	 * 
	 * @param mode The mode to go to.
	 */
	public void changeControlMode(final CANTalon.TalonControlMode mode) {
		if (leftDriveMaster.getControlMode().equals(mode)) {
			return;
		}

		leftDriveMaster.changeControlMode(mode);
		rightDriveMaster.changeControlMode(mode);

		if (mode.equals(CANTalon.TalonControlMode.PercentVbus)) {
			rightDriveMaster.setPID(0.0, 0.0, 0.0);
			rightDriveMaster.setF(0.0);

			leftDriveMaster.setF(0.0);
			leftDriveMaster.setPID(0.0, 0.0, 0.0);
		} else if (mode.equals(CANTalon.TalonControlMode.Speed)) {
			rightDriveMaster.setPID(0.24, 0.0, 0.0);
			rightDriveMaster.setF(1.8);

			leftDriveMaster.setPID(0.24, 0.0, 0.0);
			leftDriveMaster.setF(1.8);
		} else if (mode.equals(CANTalon.TalonControlMode.Position)) {
			leftDriveMaster.setPID(0.058, 0.0, 0.0);
			leftDriveMaster.setF(0.0);
			leftDriveMaster.reverseSensor(true);
			leftDriveMaster.setCloseLoopRampRate(100);

			rightDriveMaster.setPID(0.058, 0.0, 0.0);
			rightDriveMaster.setF(0.0);
			rightDriveMaster.reverseSensor(false);
			rightDriveMaster.setCloseLoopRampRate(100);
		}
	}

	/**
	 * Resets the drive trains current readings, useful before using a command.
	 */
	public void resetReadings() {
		rightDriveMaster.setPosition(0.0);
		leftDriveMaster.setPosition(0.0);

		rightDriveMaster.enable();
		leftDriveMaster.enable();
	}

	/**
	 * @return Gets if the target has been met.
	 */
	public boolean atTarget() {
		if (leftDriveMaster.getControlMode().equals(CANTalon.TalonControlMode.Position)) {
			if (Maths.nearTarget(leftDriveMaster.getEncPosition(), leftDriveMaster.getSetpoint(), 3.0 * RobotMap.Digital.DRIVE_IN_TO_ENCODER)) {
				if (Maths.nearTarget(rightDriveMaster.getEncPosition(), rightDriveMaster.getSetpoint(), 3.0 * RobotMap.Digital.DRIVE_IN_TO_ENCODER)) {
					return true;
				}
			}
		}

		return false;
	}
	
	public void setFullspeed(boolean fullspeed) {
		this.fullspeed = fullspeed;
	}
	
	public boolean isFullspeed() {
		return fullspeed;
	}

	/**
	 * Shifts the drive train into high gear.
	 */
	public void shiftHigh() {
		if (!shifter.get()) {
			shifter.set(true);
		}
	}

	/**
	 * Shifts the drive train into low gear.
	 */
	public void shiftLow() {
		if (shifter.get()) {
			shifter.set(false);
		}
	}

	/**
	 * Stops all drive train movement.
	 */
	public void stop() {
		leftDriveMaster.set(0.0);
		rightDriveMaster.set(0.0);
	}
}
