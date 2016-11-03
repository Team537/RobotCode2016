package org.team537.robot.autonomus;

import org.team537.robot.commands.ClimberRetract;
import org.team537.robot.commands.Delay;
import org.team537.robot.commands.DriveTimed;

import edu.wpi.first.wpilibj.command.CommandGroup;

public class AutoLowBar extends CommandGroup {
	public AutoLowBar() {
		addSequential(new ClimberRetract());
		addSequential(new Delay(1.0));
		addSequential(new DriveTimed(0.5, 4.20));
	}
}
