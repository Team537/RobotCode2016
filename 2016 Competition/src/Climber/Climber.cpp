#include "Climber.hpp"

void Climber::Update(bool teleop)
{
	if (teleop)
	{
		if (extenderButton->WasDown())
		{
			Extend();
		}

		if (hookButton->WasDown())
		{
			Hook();
		}
	}

	// States handled when updates called in auto.
}

void Climber::Reset()
{
	backLeftExtender->Set(0);
	frontLeftExtender->Set(0);
	backRightExtender->Set(0);
	frontRightExtender->Set(0);
	leftHook->Set(0);
	rightHook->Set(0);
}

void Climber::Extend()
{
	backLeftExtender->Set(!backLeftExtender->Get());
	frontLeftExtender->Set(!frontLeftExtender->Get());
	backRightExtender->Set(!backRightExtender->Get());
	backRightExtender->Set(!backRightExtender->Get());
}

bool Climber::GetExtended()
{
	return backLeftExtender->Get() && backRightExtender->Get();
}

void Climber::Hook()
{
	leftHook->Set(!leftHook->Get());
	rightHook->Set(!rightHook->Get());
}

bool Climber::GetHooked()
{
	return leftHook->Get() && rightHook->Get();
}