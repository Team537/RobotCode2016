#include <Shooter/Shooter.hpp>

void Shooter::Update(bool teleop)
{
    if (teleop) //  && !IsActivated()
    {
        if (aimButton->WasDown())
        {
            drive->SetState(DriveTrain::DriveState::TELEOP_SHOOT);
            state = ShooterState::AIMING_SPINNING;
        }

        if (shootButton->WasDown())
        {
            drive->SetState(DriveTrain::DriveState::TELEOP_CONTROL);
            state = ShooterState::FIRE;
        }
    }

    if (state != ShooterState::NONE)
    {
        if (drive->IsAtAngle() || state != ShooterState::AIMING_SPINNING)
        {
            drive->SetState(DriveTrain::DriveState::NONE);
        }
    }

    if (state == ShooterState::FIRE)
    {
        state = ShooterState::NONE;
    }

    /*switch(state)
     {
     case(ShooterState::NONE):
     break;
     case(ShooterState::SPINNING):
     spinSpeed = 0.62; // TODO: Calculate speed!
     spinTalon->Set(spinSpeed);

     if (fabs(spinTalon->GetSpeed()) == fabs(spinSpeed) - SHOOTER_SPEED_DEADBAND) // TODO, Deadband!
     {
     state = ShooterState::FIRE;
     }
     break;
     case(ShooterState::FIRE):
     if (extendTimer->Get())
     {
     extend->Set(true);
     extendTimer->Start();
     }

     if (2.0f - extendTimer->Get() < 0) // 2.0 seconds!
     {
     extendTimer->Stop();
     extendTimer->Reset();
     state = ShooterState::RETRACT;
     }
     break;
     case(ShooterState::RETRACT):
     spinTalon->Set(0);
     extend->Set(false);
     break;
     }*/
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
