package org.team537.robot.commands.drive;

import org.team537.robot.Robot;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;

public class DriveTimed extends Command {
	private final Timer timer;
	private final double speed, time;

	public DriveTimed(final double speed, final double time) {
		requires(Robot.drive);
		timer = new Timer();
		this.speed = speed;
		this.time = time;
	}

	/**
	 * Called just before this Command runs the first time.
	 */
	@Override
	protected void initialize() {
		timer.stop();
		timer.reset();
		timer.start();

		Robot.drive.shiftLow();
		Robot.drive.driveSpeed(speed, speed);
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
		return timer.get() > time;
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
