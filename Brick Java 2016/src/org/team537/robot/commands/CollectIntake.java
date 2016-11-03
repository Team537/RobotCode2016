package org.team537.robot.commands;

import org.team537.robot.Robot;
import org.team537.robot.RobotMap;

import edu.wpi.first.wpilibj.command.Command;

public class CollectIntake extends Command {
	private boolean reverse;
	
	public CollectIntake(boolean reverse) {
		this.reverse = reverse;
	}

	/**
	 * Called just before this Command runs the first time.
	 */
	@Override
	protected void initialize() {
		if (Robot.collector.intake.getSetpoint() == (reverse ? -1.0 : 1.0) * RobotMap.Driver.COLLECTOR_SPEED) {
			Robot.collector.intake.set(0.0);
		} else {
			Robot.collector.intake.set((reverse ? -1.0 : 1.0) * RobotMap.Driver.COLLECTOR_SPEED);
		}
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
		return Robot.collector.intake.getSetpoint() == 0.0;
	}

	/**
	 * Called once after isFinished returns true.
	 */
	@Override
	protected void end() {
		Robot.collector.intake.set(0.0);
	}

	/**
	 * Called when another command which requires one or more of the same subsystems is scheduled to run.
	 */
	@Override
	protected void interrupted() {
	}
}
