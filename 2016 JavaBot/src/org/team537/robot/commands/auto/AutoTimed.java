package org.team537.robot.commands.auto;

import org.team537.robot.commands.climber.ClimberRetract;
import org.team537.robot.commands.drive.DriveTimed;

import edu.wpi.first.wpilibj.command.CommandGroup;

public class AutoTimed extends CommandGroup {
	public AutoTimed() {
		addSequential(new ClimberRetract());
		addSequential(new DriveTimed(0.5, 2.0));
	}
}
