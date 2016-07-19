package org.team537.robot.commands;

import org.team537.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.Scheduler;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class ClimberStateDecrement extends Command {
	public ClimberStateDecrement() {
		requires(Robot.climber);
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
		if (!Robot.climber.isActivated()) {
			return;
		}

		final boolean stage1 = Robot.climber.deployedStage1();
		final boolean stage2 = Robot.climber.deployedStage2();

		if (stage1 && stage2) {
			SmartDashboard.putString("Climber State", "Stage1");
			Scheduler.getInstance().add(new ClimberStage1());
		} else if (stage1 && !stage2) {
			SmartDashboard.putString("Climber State", "Retract");
			Scheduler.getInstance().add(new ClimberRetract());
		}
	}

	/**
	 * This returns true when this Command no longer needs to run execute.
	 */
	@Override
	protected boolean isFinished() {
		return true;
	}

	/**
	 * Called once after isFinished returns true.
	 */
	@Override
	protected void end() {
	}

	/**
	 * Called when another command which requires one or more of the same subsystems is scheduled to run.
	 */
	@Override
	protected void interrupted() {
	}
}
