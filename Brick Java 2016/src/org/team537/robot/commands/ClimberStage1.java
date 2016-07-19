package org.team537.robot.commands;

import org.team537.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class ClimberStage1 extends Command {
	public ClimberStage1() {
		requires(Robot.climber);
	}

	/**
	 * Called just before this Command runs the first time.
	 */
	@Override
	protected void initialize() {
		SmartDashboard.putString("Climber State", "Stage1");
	}

	/**
	 * The execute method is called repeatedly until this Command either finishes or is canceled.
	 */
	@Override
	protected void execute() {
		Robot.climber.deployStage2(false);
		Robot.climber.deployPopup(true);
		Robot.climber.deployStage1(true);
		Robot.climber.deployHooks(false);
	}

	/**
	 * This returns true when this Command no longer needs to run execute.
	 */
	@Override
	protected boolean isFinished() {
		return Robot.climber.deployedStage1() && !Robot.climber.deployedStage2();
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
