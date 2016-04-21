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
        if (deployed == true)
        {
            DeployCollector();
        }
        else if(ReturnState > 1 && retractToFrame->WasDown())
        {
            RetractCollector();
        }
        else
        {
            HalfRetractCollector();
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

void Collector::DeployCollector()
{
    positionMotor->Set(0);
    if(positionMotor->IsFwdLimitSwitchClosed())
    {
        positionMotor->SetEncPosition(0);
    }
}

void Collector::HalfRetractCollector()
{
    positionMotor->Set(1000);
}

void Collector::RetractCollector()
{
    positionMotor->Set(2000);
}

void Collector::SetState(const int &state)
{
    ReturnState = state;
}
