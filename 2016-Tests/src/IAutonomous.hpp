#ifndef IAUTONOMUS_HPP
#define IAUTONOMUS_HPP

#include "Schematic.hpp"

class IAutonomous {
private:
	std::string name;

public:
	IAutonomous(std::string autoName) {
		name = autoName;
	}

	virtual ~IAutonomous();

	virtual void Start() {}
	virtual void Update() {}
	virtual void Stop() {}

	inline std::string GetName() { return name; }
};

#endif
