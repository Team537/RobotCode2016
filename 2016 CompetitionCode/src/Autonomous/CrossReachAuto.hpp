/*
 * CrossReachAuto.h
 *
 *  Created on: Feb 4, 2016
 *      Author: code01
 */

#ifndef SRC_CROSSREACHAUTO_H_
#define SRC_CROSSREACHAUTO_H_

#include "Schematic.hpp"
#include <DriveTrain/DriveTrain.hpp>
#include <Shooter/ShooterManager.hpp>

class CrossReachAuto {
private:
	ShooterManager *shoot;
	DriveTrain *driveTrain;
	int crossreachstate;
public:
	CrossReachAuto(SendableChooser *chooser, bool defaultChooser, DriveTrain *driveTrain, ShooterManager *shoot) : IAutonomous(chooser, defaultChooser, "Test")
	{
		crossreachstate = 0;
		this->shoot = shoot;
		this->driveTrain = driveTrain;
	}

	void Start();
	bool Run(double time);
	void Stop();

};


