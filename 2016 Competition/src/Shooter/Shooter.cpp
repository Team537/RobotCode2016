#include <Shooter/Shooter.hpp>

void Shooter::Update(bool teleop)
{
    if (teleop)
    {
        if (autoShootButton->WasDown())
        {
            state = ShooterState::AIMING_SPINNING;
            autoCycle = true;
        }

        if (manualAimButton->WasDown())
        {
            state = ShooterState::AIM;
            autoCycle = false;
        }

        if (manualShootButton->WasDown())
        {
            state = ShooterState::FIRE;
            autoCycle = false;
        }

        if (exitShootButton->WasDown())
        {
            state = ShooterState::NONE;
            autoCycle = false;
        }
    }

    switch (state)
    {
        case (ShooterState::AIM):
            drive->SetState(DriveTrain::DriveState::TELEOP_SHOOT);

            if (drive->IsWaiting() && autoCycle)
            {
                state = ShooterState::SPIN;
            }
            break;
        case (ShooterState::FIRE):
            spinSpeed = 0.62; // TODO: Calculate speed!
            talonMaster->Set(spinSpeed);

            if (fabs(talonMaster->GetSpeed()) < fabs(spinSpeed) + SHOOTER_SPEED_DEADBAND &&
                fabs(talonMaster->GetSpeed()) > fabs(spinSpeed) - SHOOTER_SPEED_DEADBAND)
            {
                spunUp = true;
            }

            if (spunUp)
            {
                if (extendTimer->Get() == 0.0f)
                {
                    extendSolenoid->Set(true);
                    extendTimer->Start();
                }

                if (extendTimer->Get() > 1.25f)
                {
                    extendTimer->Stop();
                    extendTimer->Reset();
                    state = ShooterState::NONE;
                }
            }
            break;
        case (ShooterState::NONE):
            talonMaster->Set(0);
            extendSolenoid->Set(false);
            spunUp = false;
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
