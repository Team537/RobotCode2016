#include <Climber/Climber.hpp>

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
}

void Climber::Dashboard()
{
    SmartDashboard::PutBoolean("Climber Extended", IsExtended());
    SmartDashboard::PutBoolean("Climber Hooked", IsHooked());
}

void Climber::Reset()
{
    backLeftExtender->Set(0);
    frontLeftExtender->Set(0);
    backRightExtender->Set(0);
    frontRightExtender->Set(0);
    leftHook->Set(0);
    rightHook->Set(0);
    climbing = false;
}

void Climber::Extend()
{
    backLeftExtender->Set(!backLeftExtender->Get());
    frontLeftExtender->Set(!frontLeftExtender->Get());
    backRightExtender->Set(!backRightExtender->Get());
    backRightExtender->Set(!backRightExtender->Get());
    climbing = true;
}

void Climber::Hook()
{
    leftHook->Set(!leftHook->Get());
    rightHook->Set(!rightHook->Get());
    climbing = true;
}

bool Climber::IsExtended()
{
    return backLeftExtender->Get() && backRightExtender->Get();
}

bool Climber::IsHooked()
{
    return leftHook->Get() && rightHook->Get();
}

bool Climber::IsClimbing()
{
    return climbing;
}
