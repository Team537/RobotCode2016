package org.team537.robot.commands;

import org.team537.robot.Robot;
import org.team537.robot.RobotMap;

import edu.wpi.first.wpilibj.command.Command;

public class DriveTank extends Command {
	public DriveTank() {
		requires(Robot.drive);
	}

	/**
	 * Called just before this Command runs the first time.
	 */
	@Override
	protected void initialize() {
	}

	/**
	 * The execute method is called repeatedly until this Command either finishes or is canceled.
	 */
	@Override
	protected void execute() {
		final double left = Robot.oi.joystickPrimary.getRawAxis(RobotMap.JoystickAxes.LEFT_Y);
		final double right = Robot.oi.joystickPrimary.getRawAxis(RobotMap.JoystickAxes.RIGHT_Y);
		Robot.drive.driveSpeed(left, right);
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
