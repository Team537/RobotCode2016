package org.team537.robot.commands;

import org.team537.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;

public class CollectDown extends Command {
	private boolean done;
	
	public CollectDown() {
	}

	/**
	 * Called just before this Command runs the first time.
	 */
	@Override
	protected void initialize() {
		done = false;
	}

	/**
	 * The execute method is called repeatedly until this Command either finishes or is canceled.
	 */
	@Override
	protected void execute() {
     //   Robot.collector.intake.configLimitMode(CANTalon::LimitMode::kLimitMode_SrxDisableSwitchInputs);
        Robot.collector.intake.set(0.4);

        if (Robot.collector.intake.isFwdLimitSwitchClosed())
        {
        	Robot.collector.intake.set(0.0);
        //	Robot.collector.intake.configLimitMode(CANTalon::LimitMode::kLimitMode_SoftPositionLimits);
        	Robot.collector.intake.setPosition(0.0);
        	Robot.collector.intake.enable();
            done = true;
        }
	}

	/**
	 * This returns true when this Command no longer needs to run execute.
	 */
	@Override
	protected boolean isFinished() {
		return done;
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
