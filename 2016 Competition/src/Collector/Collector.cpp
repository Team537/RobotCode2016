#include <Collector/Collector.hpp>

void Collector::Update(bool teleop)
{
    if (teleop)
    {
        if (collectInToggle->WasDown())
        {
            Collect(false);
        }

        if (collectOutButton->GetState())
        {
            Collect(true);
        }

        if (collectStop->WasDown())
        {
            Off();
        }
    }
}

void Collector::Dashboard()
{
    SmartDashboard::PutNumber("Collector Motor", collectMotor->Get());
}

void Collector::Off()
{
    collectMotor->Set(0);
}

void Collector::Collect(bool reverse)
{
    collectMotor->Set(COLLECTOR_SPEED * (reverse ? -1.0 : 1.0));
}