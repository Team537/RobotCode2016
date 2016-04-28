#include <Autonomous/AutonomousNone.hpp>

void AutonomousNone::Start()
{
}

bool AutonomousNone::Run(const double& time)
{
    climber->ToggleStage1(true);
    climber->ToggleStage2(false);
    climber->ToggleExtend(false);
    return false;
}

void AutonomousNone::Stop()
{
}
