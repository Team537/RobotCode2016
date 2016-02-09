/*
 * AutoReach.h
 *
 *  Created on: Feb 6, 2016
 *      Author: code01
 */

#include "Schematic.hpp"
#include "DriveTrain.hpp"

#ifndef SRC_AUTOREACH_HPP
#define SRC_AUTOREACH_HPP

class AutoReach {
private:
	Timer *clock;
	DriveTrain *drive;
public:
	void Init();
	void Run();
	AutoReach()
	{

	}

};

#endif /* SRC_AUTOREACH_H_ */
