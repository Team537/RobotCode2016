package org.team537.robot;

import org.team537.robot.commands.ClimberActivate;
import org.team537.robot.commands.ClimberHooks;
import org.team537.robot.commands.ClimberRetract;
import org.team537.robot.commands.ClimberStateDecrement;
import org.team537.robot.commands.ClimberStateIncrement;
import org.team537.robot.commands.DriveFullspeed;
import org.team537.robot.commands.DriveShift;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.buttons.JoystickButton;

/**
 * This class is the glue that binds the controls on the physical operator
 * interface to the commands and command groups that allow control of the robot.
 */
public class OI {
	public final Joystick joystickPrimary;
	public final Joystick secondaryPrimary;
	
	public OI() {
		joystickPrimary = new Joystick(RobotMap.Driver.PRIMARY_PORT);
		secondaryPrimary = new Joystick(RobotMap.Driver.SECONDARY_PORT);

		new JoystickButton(joystickPrimary, RobotMap.JoystickKeys.BUMPER_LEFT).whenPressed(new DriveShift(false));
		new JoystickButton(joystickPrimary, RobotMap.JoystickKeys.BUMPER_RIGHT).whenPressed(new DriveShift(true));
		
		new JoystickButton(joystickPrimary, RobotMap.JoystickKeys.Y).whenPressed(new DriveFullspeed());
		
		// new JoystickButton(joystickPrimary, RobotMap.JoystickKeys.A).whenPressed(new DriveTimed(0.5, 2.0));
		// new JoystickButton(joystickPrimary, RobotMap.JoystickKeys.Y).whenPressed(new DriveDistance(2.223, 2.223));

		new JoystickButton(joystickPrimary, RobotMap.JoystickKeys.START).whenPressed(new ClimberActivate());
		new JoystickButton(joystickPrimary, RobotMap.JoystickKeys.X).whenPressed(new ClimberHooks());
		new JoystickButton(joystickPrimary, RobotMap.JoystickKeys.B).whenPressed(new ClimberStateDecrement());
		new JoystickButton(joystickPrimary, RobotMap.JoystickKeys.A).whenPressed(new ClimberStateIncrement());
		new JoystickButton(joystickPrimary, RobotMap.JoystickKeys.BACK).whenPressed(new ClimberRetract());
	}
}
