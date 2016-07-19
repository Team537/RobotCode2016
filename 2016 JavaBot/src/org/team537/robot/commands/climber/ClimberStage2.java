package org.team537.robot.commands.climber;

import org.team537.robot.Robot;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;

public class ClimberStage2 extends Command {
	private final Timer timer;

	public ClimberStage2() {
		requires(Robot.climber);
		timer = new Timer();
	}

	/**
	 * Called just before this Command runs the first time.
	 */
	@Override
	protected void initialize() {
		timer.stop();
		timer.reset();
	}

	/**
	 * The execute method is called repeatedly until this Command either finishes or is canceled.
	 */
	@Override
	protected void execute() {
		if (timer.get() > 1.25f) {
			timer.stop();
			timer.reset();
			Robot.climber.deployPopup(false);
		}

		if (timer.get() > 0.0f) {
			if (!Robot.climber.deployedStage1()) {
				Robot.climber.deployPopup(true);
				Robot.climber.deployStage1(true);
				timer.start();
			} else if (!Robot.climber.deployedStage2()) {
				Robot.climber.deployStage2(true);
			}
		}
	}

	/**
	 * This returns true when this Command no longer needs to run execute.
	 */
	@Override
	protected boolean isFinished() {
		return timer.get() == 0 && Robot.climber.deployedStage1() && Robot.climber.deployedStage2();
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
