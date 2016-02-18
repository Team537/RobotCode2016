#include <Collector/Collector.hpp>

void Collector::Update(bool teleop)
{
    if (teleop)
    {
        if (extendButton->WasDown())
        {
            Extend();
        }

        if (leftCollectButton->GetState())
        {
            CollectLeft();
        }

        if (rightCollectButton->GetState())
        {
            CollectRight();
        }
    }
}

void Collector::Dashboard()
{
    SmartDashboard::PutNumber("Collector Extend", IsExtended());
    SmartDashboard::PutNumber("Collector Left Motor", leftMotor->Get());
    SmartDashboard::PutNumber("Collector Right Motor", rightMotor->Get());
}

void Collector::Reset()
{
    piston->Set(false);
    leftMotor->Set(0);
    rightMotor->Set(0);
}

void Collector::Extend()
{
    piston->Set(!piston->Get());
}

void Collector::CollectLeft()
{
    leftMotor->Set(0.75f);
}

void Collector::CollectRight()
{
    rightMotor->Set(0.75f);
}

bool Collector::IsExtended()
{
    return piston->Get();
}
