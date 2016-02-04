#include <Collector/CollectorManager.hpp>

void CollectorManager::Collect(bool BTN1, bool BTN2) {
	switch (btnState) {
	case 0:
		if (BTN1 && speed == 0) {
			btnState = 1;
		}

		if (BTN1 && speed == 1) {
			btnState = 2;
		}

		break;
	case 1:
		speed = 1;

		if (!BTN1) {
			btnState = 0;
		}

		break;
	case 2:
		speed = 0;

		if (!BTN1) {
			btnState = 0;
		}

		break;
	}

	if (BTN2) {
		speed = -1;
	}

	Motor->SetSpeed(speed);
}

void CollectorManager::Extend(bool BTN)
{
	if (BTN) {
		Pistons->Set(!Pistons->Get());
	}
}
