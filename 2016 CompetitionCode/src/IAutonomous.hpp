#ifndef IAUTONOMUS_HPP
#define IAUTONOMUS_HPP

#include <Schematic.hpp>

using namespace std;

class IAutonomous {
private:
	string name;
	bool started;

public:
	IAutonomous(SendableChooser *chooser, bool defaultChooser, string autoName) {
		name = autoName;
		started = false;

		if (defaultChooser)
		{
			chooser->AddDefault(name, this);
		}
		else
		{
			chooser->AddObject(name, this);
		}
	}

	bool AutonomousUpdate(double time)
	{
		if (!started)
		{
			Start();
			started = true;
		}
		else
		{
			bool running = Run(time);

			if ((time > 15 || started) ? !Run(1000) : false || !running)
			{
				Stop();
				return (started = false);
			}
		}

		return true;
	}

	virtual void Start() {}
	virtual bool Run(double time) { return false; }
	virtual void Stop() {}

	inline string GetName() { return name; }
};

#endif
