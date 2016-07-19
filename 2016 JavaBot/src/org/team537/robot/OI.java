package org.team537.robot;

import org.team537.robot.commands.climber.ClimberActivate;
import org.team537.robot.commands.climber.ClimberHooks;
import org.team537.robot.commands.climber.ClimberStateDecrement;
import org.team537.robot.commands.climber.ClimberStateIncrement;
import org.team537.robot.commands.drive.DriveShiftHigh;
import org.team537.robot.commands.drive.DriveShiftLow;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.buttons.JoystickButton;

/**
 * This class is the glue that binds the controls on the physical operator interface to the commands and command groups that allow control of the robot.
 */
public class OI {
	public final Joystick primaryJoystick;
	public final Joystick secondaryJoystick;

	public OI() {
		primaryJoystick = new Joystick(RobotMap.Driver.PRIMARY_PORT);
		secondaryJoystick = new Joystick(RobotMap.Driver.SECONDARY_PORT);

		new JoystickButton(primaryJoystick, RobotMap.JoystickKeys.BUMPER_LEFT).whenPressed(new DriveShiftLow());
		new JoystickButton(primaryJoystick, RobotMap.JoystickKeys.BUMPER_RIGHT).whenPressed(new DriveShiftHigh());

		new JoystickButton(secondaryJoystick, RobotMap.JoystickKeys.START).whenPressed(new ClimberActivate());
		new JoystickButton(secondaryJoystick, RobotMap.JoystickKeys.A).whenPressed(new ClimberHooks());
		new JoystickButton(secondaryJoystick, RobotMap.JoystickKeys.BUMPER_LEFT).whenPressed(new ClimberStateDecrement());
		new JoystickButton(secondaryJoystick, RobotMap.JoystickKeys.BUMPER_RIGHT).whenPressed(new ClimberStateIncrement());
	}
}
