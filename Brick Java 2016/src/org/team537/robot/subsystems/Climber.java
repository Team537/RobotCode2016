package org.team537.robot.subsystems;

import org.team537.robot.RobotMap;
import org.team537.robot.commands.ClimberNone;

import edu.wpi.first.wpilibj.Solenoid;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Climber extends Subsystem {
	private final Solenoid deployStage1 = new Solenoid(RobotMap.Solenoid.CLIMBER_STAGE1);
	private final Solenoid deployStage2 = new Solenoid(RobotMap.Solenoid.CLIMBER_STAGE2);
	private final Solenoid deployHooks = new Solenoid(RobotMap.Solenoid.CLIMBER_HOOKS);
	private final Solenoid deployPopup = new Solenoid(RobotMap.Solenoid.CLIMBER_POPUP);

	private boolean activated;

	public Climber() {
		activated = false;
	}

	@Override
	protected void initDefaultCommand() {
		setDefaultCommand(new ClimberNone());
	}

	/**
	 * Updates the subsystems dashboard readings.
	 */
	public void dashboard() {
		SmartDashboard.putBoolean("Climbing", activated);

		SmartDashboard.putBoolean("Climber Stage 1", deployedStage1());
		SmartDashboard.putBoolean("Climber Stage 2", deployedStage2());
		SmartDashboard.putBoolean("Climber Stage Hooks", deployedHooks());
		SmartDashboard.putBoolean("Climber Popup", deployedPopup());
	}

	/**
	 * @return If stage 1 readings say they are deployed.
	 */
	public boolean deployedStage1() {
		return !deployStage1.get();
	}

	/**
	 * @return If stage 2 readings say they are deployed.
	 */
	public boolean deployedStage2() {
		return deployStage2.get();
	}

	/**
	 * @return If hooks were deployed.
	 */
	public boolean deployedHooks() {
		return deployHooks.get();
	}

	/**
	 * @return If the stage 1 assist is deployed.
	 */
	public boolean deployedPopup() {
		return deployPopup.get();
	}

	/**
	 * Deploys climber stage 1.
	 * 
	 * @param deploy If the stage should deploy.
	 */
	public void deployStage1(boolean deploy) {
		deployStage1.set(!deploy);
	}

	/**
	 * Deploys climber stage 2.
	 * 
	 * @param deploy If the stage should deploy.
	 */
	public void deployStage2(boolean deploy) {
		deployStage2.set(deploy);
	}

	/**
	 * Deploys climber stage 3.
	 * 
	 * @param deploy If the stage should deploy.
	 */
	public void deployHooks(boolean deploy) {
		deployHooks.set(deploy);
	}

	/**
	 * Deploys climber stage 1's assist.
	 * 
	 * @param deploy If the popup should deploy.
	 */
	public void deployPopup(boolean deploy) {
		deployPopup.set(deploy);
	}

	/**
	 * @return If the climber is activated.
	 */
	public boolean isActivated() {
		return activated;
	}

	/**
	 * Changes if the climber is activated.
	 * 
	 * @param activate If the climber should go active.
	 */
	public void setActivated(boolean activate) {
		activated = activate;
	}
}
