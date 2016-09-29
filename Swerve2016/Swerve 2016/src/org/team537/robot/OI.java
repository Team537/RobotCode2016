package org.team537.robot;

import edu.wpi.first.wpilibj.Joystick;

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

	}
}
