#include <Collector/Collector.hpp>

void Collector::Update(bool teleop)
{
    if (teleop)
    {
        if (CollectButton->GetState())
        {
            Collect();
        }
        else
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

void Collector::Collect()
{
    collectMotor->Set(COLLECTOR_SPEED);
}
