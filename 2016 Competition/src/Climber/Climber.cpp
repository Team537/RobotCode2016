#include <Climber/Climber.hpp>

void Climber::Update(bool teleop)
{
    // TODO: Check before a bot is broken!

    if (teleop)
    {
        if (startClimbing->WasDown())
        {
            climbing = !climbing;
        }

        if (halfDeployButton->WasDown())
        {
            deployStage1->Set(true);
        }

        if (fullDeployButton->WasDown())
        {
            deployStage1->Set(true);
            deployStage2->Set(true);
            climberExtend->Set(true);
        }

        if (retractButton->WasDown())
        {
            deployStage1->Set(false);
            deployStage2->Set(false);
            climberExtend->Set(false);
        }

        if (pullUpButton->WasDown())
        {
            deployStage1->Set(false);
            deployStage2->Set(false);
            climberExtend->Set(true);
        }

        switch(state)
        {
            case RETRACTED:
                break;
            case DEPLOYED_HALF:
                break;
            case DEPLOYED_FULL:
                break;
            case PULL_UP:
                break;
        }
    }

    if (!climbing)
    {
        deployStage1->Set(false);
        deployStage2->Set(false);
        climberExtend->Set(false);
    }
}

void Climber::Dashboard()
{
    SmartDashboard::PutBoolean("Climber Stage 1", deployStage1->Get());
    SmartDashboard::PutBoolean("Climber Stage 2", deployStage2->Get());
    SmartDashboard::PutBoolean("Climber Extender", climberExtend->Get());
}

bool Climber::IsClimbing()
{
    return climbing;
}
