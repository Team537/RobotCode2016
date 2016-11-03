package org.team537.robot.subsystems;

import org.team537.robot.RobotMap;

import edu.wpi.first.wpilibj.CANTalon;
import edu.wpi.first.wpilibj.command.Subsystem;

public class Collector extends Subsystem {
	public final CANTalon position = new CANTalon(RobotMap.CAN.COLLECT_POSITION);
	public final CANTalon intake = new CANTalon(RobotMap.CAN.COLLECT_INTAKE);

	public Collector() {
		position.changeControlMode(CANTalon.TalonControlMode.PercentVbus);
		position.setFeedbackDevice(CANTalon.FeedbackDevice.QuadEncoder);
		position.ConfigRevLimitSwitchNormallyOpen(true);
		position.setPID(20.0, 0.0, 0.0);
		position.configEncoderCodesPerRev(1);
	//	position.configLimitMode(CANTalon::LimitMode::kLimitMode_SoftPositionLimits);
		position.setForwardSoftLimit(0.0);
		position.setReverseSoftLimit(-6130.0);
		position.setPosition(0);
		position.enable();

        intake.changeControlMode(CANTalon.TalonControlMode.PercentVbus);
        intake.enable();
	}
	
	@Override
	protected void initDefaultCommand() {
	}

	/**
	 * Updates the subsystems dashboard readings.
	 */
	public void dashboard() {
	}
}
