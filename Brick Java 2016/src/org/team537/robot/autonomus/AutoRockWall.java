package org.team537.robot.autonomus;

import org.team537.robot.commands.ClimberRetract;
import org.team537.robot.commands.Delay;
import org.team537.robot.commands.DriveTimed;

import edu.wpi.first.wpilibj.command.CommandGroup;

public class AutoRockWall extends CommandGroup {
	public AutoRockWall() {
		addSequential(new ClimberRetract());
		addSequential(new Delay(1.2));
		addSequential(new DriveTimed(0.75, 4.0));
	}
}
