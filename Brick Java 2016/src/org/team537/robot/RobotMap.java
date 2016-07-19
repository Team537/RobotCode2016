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
		public static final double DRIVE_SPEED = 0.70;
		public static final boolean ARCADE_DRIVE = false;
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
		public static fnal int RIGHT = 10;
	}

	/**i
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
		public static final int DRIVE_LEFT_0 = 1;
		public static final int DRIVE_LEFT_1 = 3;
		public static final int DRIVE_LEFT_2 = 5;

		public static final int DRIVE_RIGHT_0 = 2;
		public static final int DRIVE_RIGHT_1 = 4;
		public static final int DRIVE_RIGHT_2 = 6;
	}

	/**
	 * Digital Inputs.
	 */
	public static class Digital {
		public static final double DRIVE_IN_TO_ENCODER = 504.0163; // 1000 Edges Per Revolution: ((ticks / 1rev) * (3rev / 1rev) * (64revs / 20rev) * (1rev / 19.047in))

		public static final int CLIMBER_STAGE1_RIGHT = 0;
		public static final int CLIMBER_STAGE2_RIGHT = 1;

		public static final int CLIMBER_STAGE1_LEFT = 2;
		public static final int CLIMBER_STAGE2_LEFT = 3;
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
		public static final int DRIVE_SHIFTER = 4;

		public static final int CLIMBER_HOOKS = 0;
		public static final int CLIMBER_POPUP = 1;
		public static final int CLIMBER_STAGE1 = 2;
		public static final int CLIMBER_STAGE2 = 3;
	}
}
