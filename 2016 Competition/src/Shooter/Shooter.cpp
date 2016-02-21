#include <Shooter/Shooter.hpp>

void Shooter::Update(bool teleop)
{
    if (teleop)
    {
        if (autoShootButton->WasDown())
        {
            drive->SetState(DriveTrain::DriveState::TELEOP_SHOOT);
            state = ShooterState::NONE;
        }
    }

    switch (state)
    {
        case (ShooterState::AIMING_SPINNING):
            break;
            spinSpeed = 0.62; // TODO: Calculate speed!
            talonMaster->Set(spinSpeed);

            if (drive->IsWaiting() && fabs(talonMaster->GetSpeed()) == fabs(spinSpeed) - SHOOTER_SPEED_DEADBAND) // TODO, Deadband!
            {
                state = ShooterState::FIRE;
            }
            break;
        case (ShooterState::FIRE):
            if (extendTimer->Get())
            {
                extendSolenoid->Set(true);
                extendTimer->Start();
            }

            if (1.0f - extendTimer->Get() < 0)
            {
                extendTimer->Stop();
                extendTimer->Reset();
                state = ShooterState::NONE;
            }
            break;
        case (ShooterState::NONE):
            talonMaster->Set(0);
            extendSolenoid->Set(false);
            break;
    }
}

void Shooter::Dashboard()
{
    SmartDashboard::PutBoolean("Shooter Activated", IsActivated());
    SmartDashboard::PutBoolean("Shooter Speed", spinSpeed);
}

bool Shooter::IsActivated()
{
    return state != ShooterState::NONE;
}
