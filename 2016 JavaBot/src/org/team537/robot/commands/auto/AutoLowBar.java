package org.team537.robot.commands.auto;

import org.team537.robot.commands.climber.ClimberRetract;
import org.team537.robot.commands.drive.DriveDistance;

import edu.wpi.first.wpilibj.command.CommandGroup;

public class AutoLowBar extends CommandGroup {
	public AutoLowBar() {
		addSequential(new ClimberRetract());
		addSequential(new DriveDistance(2.447, 2.447));
	}
}
