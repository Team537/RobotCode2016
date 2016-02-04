#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP

#include <WPILib.h>

class CollectorManager {
private:
	Solenoid *Pistons;
	Victor *Motor;
	int btnState = 0;
	float speed = 0;

	CollectorManager() {
		Pistons = new Solenoid(1);
		Motor = new Victor(1);
	}
public:
	void Extend(bool BTN);
	void Collect(bool BTN1, bool BTN2);
};

#endif
