package org.team537.robot.commands;

import org.team537.robot.Robot;
import org.team537.robot.RobotMap;

import edu.wpi.first.wpilibj.command.Command;

public class DriveDefault extends Command {
	public DriveDefault() {
		requires(Robot.drive);
	}

	/**
	 * Called just before this Command runs the first time.
	 */
	@Override
	protected void initialize() {
		Robot.drive.reset();
	}

	/**
	 * The execute method is called repeatedly until this Command either finishes or is canceled.
	 */
	@Override
	protected void execute() {
		double rotation = Robot.oi.joystickPrimary.getRawAxis(RobotMap.JoystickAxes.RIGHT_X);
		double strafe = Robot.oi.joystickPrimary.getRawAxis(RobotMap.JoystickAxes.LEFT_X);
		double forward = -Robot.oi.joystickPrimary.getRawAxis(RobotMap.JoystickAxes.LEFT_Y);
		double gyro = 0.0; // Robot.ahrs.getAngle();
		Robot.drive.drive(rotation, strafe, forward, gyro);
	}

	/**
	 * This returns true when this Command no longer needs to run execute.
	 */
	@Override
	protected boolean isFinished() {
		return false;
	}

	/**
	 * Called once after isFinished returns true.
	 */
	@Override
	protected void end() {
		Robot.drive.stop();
	}

	/**
	 * Called when another command which requires one or more of the same subsystems is scheduled to run.
	 */
	@Override
	protected void interrupted() {
	}
}
