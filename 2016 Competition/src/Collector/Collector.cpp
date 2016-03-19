#include <Collector/Collector.hpp>

void Collector::Update(const bool& teleop)
{
    if (teleop)
    {
        // Intakes if the toggle was pressed.
        if (collectInToggle->WasDown())
        {
            Collect(false);
        }
        // Stop collecting if stop toggle was pressed.
        else if (collectStop->WasDown())
        {
            TurnOff();
        }

        // Spits out while held down.
        if (collectOutButton->GetState())
        {
            Collect(true);
            reverseCollecting = true;
        }
        // Stop collecting if not held down.
        else if (reverseCollecting && !collectOutButton->GetState())
        {
            TurnOff();
            reverseCollecting = false;
        }
    }
}

void Collector::Dashboard()
{
    SmartDashboard::PutNumber("Collector Motor Speed", collectMotor->Get());
}

void Collector::Collect(const bool& reverse)
{
    collectMotor->Set(COLLECTOR_SPEED * (reverse ? 1.0 : -1.0));
}

void Collector::TurnOff()
{
    collectMotor->Set(0);
}
