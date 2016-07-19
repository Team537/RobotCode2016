package org.team537.robot;

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into to a variable name. 
 * This provides flexibility changing wiring, makes checking the wiring easier and significantly 
 * reduces the number of magic numbers floating around.
 */
public class RobotMap {
	/**
	 * Driver Controls.
	 */
	public static class Driver {
		public static final int PRIMARY_PORT = 0;
		public static final int SECONDARY_PORT = 1;
	}

	/**
	 * Robot Dimensions.
	 */
	public static class Robot {
		public static final double WIDTH = 26.0;
		public static final double LENGTH = 26.0;
		public static final double RATIO = Math.sqrt((LENGTH * LENGTH) + (WIDTH * WIDTH));
	}
	
	/**
	 * Joystick Keys.
	 */
	public static class JoystickKeys {
		public static final int A = 1;
		public static final int B = 2;
		public static final int X = 3;
		public static final int Y = 4;
		public static final int BUMPER_LEFT = 5;
		public static final int BUMPER_RIGHT = 6;
		public static final int BACK = 7;
		public static final int START = 8;
		public static final int LEFT = 9;
		public static final int RIGHT = 10;
	}

	/**
	 * Joystick Axes.
	 */
	public static class JoystickAxes {
		public static final int LEFT_X = 0;
		public static final int LEFT_Y = 1;
		public static final int TRIGGER_LEFT = 2;
		public static final int TRIGGER_RIGHT = 3;
		public static final int RIGHT_X = 4;
		public static final int RIGHT_Y = 5;
	}

	/**
	 * PWM Channels.
	 */
	public static class PWM {
	}

	/**
	 * CAN bus Channels.
	 */
	public static class CAN {
		// TODO CHECK
		public static final int DRIVE_BACK_LEFT_ANGLE = 4;
		public static final int DRIVE_BACK_LEFT_DRIVE = 3;

		public static final int DRIVE_BACK_RIGHT_ANGLE = 5;
		public static final int DRIVE_BACK_RIGHT_DRIVE = 6;

		public static final int DRIVE_FRONT_LEFT_ANGLE = 2;
		public static final int DRIVE_FRONT_LEFT_DRIVE = 1;

		public static final int DRIVE_FRONT_RIGHT_ANGLE = 7;
		public static final int DRIVE_FRONT_RIGHT_DRIVE = 8;
	}

	/**
	 * Digital Inputs.
	 */
	public static class Digital {
	}

	/**
	 * Analog Inputs.
	 */
	public static class Analog {
	}

	/**
	 * Solenoids.
	 */
	public static class Solenoid {
	}
}
