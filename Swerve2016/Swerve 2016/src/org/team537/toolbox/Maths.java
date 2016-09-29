package org.team537.toolbox;

/**
 * A class that holds many various math functions.
 */
public class Maths {
	public static double PI = 3.14159265358979323846;
	public static double DEGREES_IN_CIRCLE = 360.0;
	public static double DEGREES_IN_HALF_CIRCLE = 180.0;
	public static double ANG2RAD = PI / DEGREES_IN_HALF_CIRCLE;
	public static double LOG_HALF = Math.log(0.5);

	/**
	 * Gets the maximum value.
	 *
	 * @param fs The values to sort though.
	 *
	 * @return The maximum value.
	 */
	public static double maxValue(double... fs) {
		double max = 0.0;

		for (double v : fs) {
			if (v > max) {
				max = v;
			}
		}

		return max;
	}

	/**
	 * Gets the minimum value.
	 *
	 * @param fs The values to sort though.
	 *
	 * @return The minimum value.
	 */
	public static double minValue(double... fs) {
		double min = 0.0;

		for (double v : fs) {
			if (v < min) {
				min = v;
			}
		}

		return min;
	}

	/**
	 * Gets if a value is near to the target.
	 * 
	 * @param value The current value reading.
	 * @param target The target to get to.
	 * @param tolerance The allowed tolerance.
	 * 
	 * @return If the value is acceptable under the tolerance.
	 */
	public static boolean nearTarget(double value, double target, double tolerance) {
		return Math.abs(value - target) < tolerance;
	}

	/**
	 * Normalizes a angle into the range of 0-360.
	 *
	 * @param angle The source angle.
	 *
	 * @return The normalized angle.
	 */
	public static double normalizeAngle(double angle) {
		if (angle >= 360.0) {
			return angle - 360.0;
		} else if (angle < 0) {
			return angle + 360.0;
		}

		return angle;
	}

	/**
	 * Used to floor the value if less than the min.
	 *
	 * @param min The minimum value.
	 * @param value The value.
	 *
	 * @return Returns a value with deadband applied.
	 */
	public static double deadband(double min, double value) {
		return Math.abs(value) >= Math.abs(min) ? value : 0.0;
	}

	/**
	 * Ensures {@code value} is in the range of {@code min} to {@code max}. If {@code value} is greater than {@code max}, this will return {@code max}. If {@code value} is less than {@code min}, this will return {@code min}. Otherwise, {@code value} is returned unchanged.
	 *
	 * @param value The value to clamp.
	 * @param min The smallest value of the result.
	 * @param max The largest value of the result.
	 *
	 * @return {@code value}, clamped between {@code min} and {@code max}.
	 */
	public static double clamp(double value, double min, double max) {
		return value < min ? min : value > max ? max : value;
	}

	/**
	 * Limits the value.
	 *
	 * @param value The value.
	 * @param limit The limit.
	 *
	 * @return A limited value.
	 */
	public static double limit(double value, double limit) {
		return value > limit ? limit : value;
	}

	/**
	 * Interpolates two values by a blendFactor using cos interpolation.
	 *
	 * @param a The first value.
	 * @param b The second value.
	 * @param blend The blend value.
	 *
	 * @return Returns a interpolated value.
	 */
	public static double cosInterpolate(double a, double b, double blend) {
		double ft = blend * Math.PI;
		double f = (1f - Math.cos(ft)) * 0.5;
		return a * (1.0 - f) + b * f;
	}
}
