package org.team537.robot.commands;

import org.team537.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;

public class DriveDistance extends Command {
	private double distanceLeft;
	private double distanceRight;

	public DriveDistance(double distanceLeft, double distanceRight) {
		requires(Robot.drive);
		this.distanceLeft = distanceLeft;
		this.distanceRight = distanceRight;
	}

	/**
	 * Called just before this Command runs the first time.
	 */
	@Override
	protected void initialize() {
		Robot.drive.shiftLow();
		Robot.drive.driveDistance(distanceLeft, distanceRight);
	}

	/**
	 * The execute method is called repeatedly until this Command either finishes or is canceled.
	 */
	@Override
	protected void execute() {
	}

	/**
	 * This returns true when this Command no longer needs to run execute.
	 */
	@Override
	protected boolean isFinished() {
		return Robot.drive.atTarget();
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
