package org.team537.robot.subsystems;

import org.team537.robot.Robot;
import org.team537.robot.RobotMap;
import org.team537.robot.commands.DriveDefault;
import org.team537.toolbox.Maths;

import edu.wpi.first.wpilibj.CANTalon;
import edu.wpi.first.wpilibj.CANTalon.FeedbackDevice;
import edu.wpi.first.wpilibj.CANTalon.TalonControlMode;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Drive extends Subsystem {
	private final DriveModule backLeft = new DriveModule(
			"Back Left", 
			new CANTalon(RobotMap.CAN.DRIVE_BACK_LEFT_ANGLE), 
			new CANTalon(RobotMap.CAN.DRIVE_BACK_LEFT_DRIVE), 
			0.0, 0.0, 0.0
	);

	private final DriveModule backRight = new DriveModule(
			"Back Right", 
			new CANTalon(RobotMap.CAN.DRIVE_BACK_RIGHT_ANGLE), 
			new CANTalon(RobotMap.CAN.DRIVE_BACK_RIGHT_DRIVE), 
			0.0, 0.0, 0.0
	);

	private final DriveModule frontLeft = new DriveModule(
			"Front Left", 
			new CANTalon(RobotMap.CAN.DRIVE_FRONT_LEFT_ANGLE), 
			new CANTalon(RobotMap.CAN.DRIVE_FRONT_LEFT_DRIVE), 
			0.0, 0.0, 0.0
	);

	private final DriveModule frontRight = new DriveModule(
			"Front Right", 
			new CANTalon(RobotMap.CAN.DRIVE_FRONT_RIGHT_ANGLE), 
			new CANTalon(RobotMap.CAN.DRIVE_FRONT_RIGHT_DRIVE), 
			0.0, 0.0, 0.0
	);

	public Drive() {
	}

	@Override
	protected void initDefaultCommand() {
		setDefaultCommand(new DriveDefault());
	}
	
	public void dashboard() {
		backLeft.dashboard();
		backRight.dashboard();
		frontLeft.dashboard();
		frontRight.dashboard();
	}
	
	public void drive(double rotation, double strafe, double forward, double gyro) {
		SmartDashboard.putNumber("Drive Input Rotation", rotation);
		SmartDashboard.putNumber("Drive Input Strafe", strafe);
		SmartDashboard.putNumber("Drive Input Forward", forward);
		SmartDashboard.putNumber("Drive Input Gyro", gyro);
		
		double angleSetpoint = Math.abs(forward) == 1 ? 180.0 : 0.0;

		backLeft.set(0.0, angleSetpoint);
		backRight.set(0.0, angleSetpoint);
		frontLeft.set(0.0, angleSetpoint);
		frontRight.set(0.0, angleSetpoint);
	}
	
	public void reset() {
		backLeft.reset();
		backRight.reset();
		frontLeft.reset();
		frontRight.reset();
		Robot.ahrs.reset();
	}
	
	public void stop() {
		backLeft.stop();
		backRight.stop();
		frontLeft.stop();
		frontRight.stop();
	}
	
	public static class DriveModule {
		private String name;
		private CANTalon angle;
		private CANTalon drive;
		
		public DriveModule(String name, CANTalon angle, CANTalon drive, double p, double i, double d) {
			this.name = name;
			this.angle = angle;
			this.drive = drive;

			this.angle.setFeedbackDevice(FeedbackDevice.AnalogPot);
			this.angle.changeControlMode(TalonControlMode.Position);
			this.angle.setPID(p, i, d);
			
			this.drive.setFeedbackDevice(FeedbackDevice.QuadEncoder);
			this.drive.changeControlMode(TalonControlMode.PercentVbus);
		}
		
		public void set(double speed, double angle) {
			SmartDashboard.putNumber(name + " Maths Speed", speed);
			SmartDashboard.putNumber(name + " Maths Angle", angle);

			this.angle.set((angle + 180.0) * (1024.0 / 360.0));
			this.drive.set(speed * 12.0);
		}
		
		public void dashboard() {
			SmartDashboard.putNumber(name + " Drive Speed", drive.getSpeed());
			SmartDashboard.putNumber(name + " Drive (Encoder)", drive.getEncPosition());
			SmartDashboard.putNumber(name + " Angle", angle.getAnalogInRaw());
		}
		
		public void reset() {
			angle.enable();
			drive.enable();

			drive.setPosition(0.0);
		}
		
		public void stop() {
			drive.set(0.0);
		}
	}
}