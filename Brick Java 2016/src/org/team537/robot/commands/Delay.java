package org.team537.robot.commands;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;

public class Delay extends Command {
	private Timer timer;
	private double time;

	public Delay(double time) {
		timer = new Timer();
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
		timer.stop();
	}

	/**
	 * Called when another command which requires one or more of the same subsystems is scheduled to run.
	 */
	@Override
	protected void interrupted() {
	}
}
