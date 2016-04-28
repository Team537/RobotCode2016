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
        if (collectOutButton->GetKey())
        {
            Collect(true);
            reverseCollecting = true;
        }
        // Stop collecting if not held down.
        else if (reverseCollecting && !collectOutButton->GetKey())
        {
            TurnOff();
            reverseCollecting = false;
        }

        if(toggleDeploy->WasDown())
        {
            deployed = !deployed;
        }

        if(retractToFrame->WasDown())
        {
            RetractCollector();
        }

        if (deployed)
        {
            DeployCollector();
        }
        else
        {
            HalfRetractCollector();
        }

        switch (collectState)
        {
            case INIT:
                positionMotor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
                positionMotor->Set(0.4);
                if (positionMotor->IsFwdLimitSwitchClosed())
                {
                    positionMotor->Set(0);
                    positionMotor->Disable();
                    positionMotor->SetControlMode(CANTalon::ControlMode::kPosition);
                    positionMotor->SetEncPosition(0);
                    positionMotor->Enable();
                    collectState = TEST;
                }
                break;
            case RETRACT:
                positionMotor->Set(4000);
                break;
            case DEPLOY_HALF:
                positionMotor->Set(2000);
                break;
            case DEPLOY_FULL:
                positionMotor->Set(0);
                if(positionMotor->IsFwdLimitSwitchClosed())
                {
                    positionMotor->SetEncPosition(0);
                }
                break;
            case TEST:
                if (toggleDeploy->GetKey())
                {
                    positionMotor->Set(positionMotor->GetEncPosition() + 1);
                }
                if (retractToFrame->GetKey())
                {
                    positionMotor->Set(positionMotor->GetEncPosition() - 1);
                }
        }
    }
}

void Collector::Dashboard()
{
    SmartDashboard::PutNumber("Collector Motor Speed", collectMotor->Get());
    SmartDashboard::PutNumber("Collector State", collectState);
    SmartDashboard::PutNumber("Collector Error", positionMotor->GetClosedLoopError());
    SmartDashboard::PutNumber("Collector Output", positionMotor->Get());
    SmartDashboard::PutNumber("Collector Setpoint", positionMotor->GetSetpoint());
    SmartDashboard::PutNumber("Collector Encoder Pos", positionMotor->GetEncPosition());
    SmartDashboard::PutNumber("Collector Limit Switch", positionMotor->IsFwdLimitSwitchClosed());
}

void Collector::Collect(const bool& reverse)
{
    collectMotor->Set(COLLECTOR_SPEED * (reverse ? 1.0 : -1.0));
}

void Collector::TurnOff()
{
    collectMotor->Set(0);
}

void Collector::HalfRetractCollector()
{
    collectState = DEPLOY_HALF;
}

void Collector::RetractCollector()
{
    collectState = RETRACT;
}

void Collector::DeployCollector()
{
    collectState = DEPLOY_FULL;
}

void Collector::SetState(const int &state)
{
    returnState = state;
}

bool Collector::IsCollecting()
{
    return collectState != RETRACT;
}

bool Collector::IsCollectorDeployed()
{
    return collectState = DEPLOY_FULL;
}
