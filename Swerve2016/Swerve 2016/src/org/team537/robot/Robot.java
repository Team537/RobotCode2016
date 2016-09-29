package org.team537.robot;

import org.team537.robot.subsystems.Drive;

import com.kauailabs.navx.frc.AHRS;

import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.SPI;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.Scheduler;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;
import edu.wpi.first.wpilibj.smartdashboard.SendableChooser;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Robot extends IterativeRobot {
	// Subsystems.
	public static Drive drive;

	// Interfaces.
	public static OI oi;
	public static AHRS ahrs;

	// Autonomous.
	private SendableChooser autoChooser;
	private Command autoCommand;
	
	private Compressor compressor;

	/**
	 * This function is for robot-wide initialization code.
	 */
	@Override
	public void robotInit() {
		// Subsystems.
		drive = new Drive();

		// Interfaces.
		oi = new OI();

		try {
			ahrs = new AHRS(SPI.Port.kMXP);
		} catch (final RuntimeException ex) {
			DriverStation.reportError("Error instantiating navX MXP: " + ex.getMessage(), true);
		}

		// Autonomous chooser to display on the dashboard.
		autoChooser = new SendableChooser();
		autoChooser.addObject("Nothing", null);
		SmartDashboard.putData("Autonomous", autoChooser);
		
		compressor = new Compressor();
		compressor.setClosedLoopControl(true);
	}

	/**
	 * This function is called when the disabled button is hit.
	 */
	@Override
	public void disabledInit() {
		if (autoCommand != null) {
			autoCommand.cancel();
		}
	}

	/**
	 * Periodic code for disabled mode should go here.
	 */
	@Override
	public void disabledPeriodic() {
		Scheduler.getInstance().run();
	}

	/**
	 * This function is called at the start of autonomous period.
	 */
	@Override
	public void autonomousInit() {
		// Schedules the autonomous command.
		autoCommand = (Command) autoChooser.getSelected();

		if (autoCommand != null) {
			autoCommand.start();
		}
	}

	/**
	 * This function is called periodically during autonomous.
	 */
	@Override
	public void autonomousPeriodic() {
		Scheduler.getInstance().run();
		dashboard();
	}

	/**
	 * This function is called at the start of operator control period.
	 */
	@Override
	public void teleopInit() {
		// This makes sure that the autonomous stops running when teleop starts running.
		if (autoCommand != null) {
			autoCommand.cancel();
			autoCommand = null;
		}
	}

	/**
	 * This function is called periodically during operator control.
	 */
	@Override
	public void teleopPeriodic() {
		Scheduler.getInstance().run();
		dashboard();
	}

	/**
	 * This function is called periodically during test mode.
	 */
	@Override
	public void testPeriodic() {
		LiveWindow.run();
		dashboard();
	}

	/**
	 * Updates the subcomponents dashboard readings.
	 */
	private void dashboard() {
		drive.dashboard();
	}
}
