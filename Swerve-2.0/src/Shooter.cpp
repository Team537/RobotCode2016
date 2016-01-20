#include "Shooter.hpp"

void Shooter::Update() {
	vision->Update();

	if (activateButton->WasDown()) {
		activated = !activated;
	}
}

void Shooter::Dashboard() {
	vision->Dashboard();
}

bool Shooter::IsActivated() {
	return activated;
}
