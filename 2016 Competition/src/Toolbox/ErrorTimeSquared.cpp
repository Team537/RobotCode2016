#include <Toolbox/ErrorTimeSquared.hpp>

void ErrorTimeSquared::Enable()
{
    rampTimer->Reset();
    rampTimer->Start();
}

void ErrorTimeSquared::Disable()
{
    rampTimer->Stop();
}

void ErrorTimeSquared::Update()
{
    float e = GetError();

    if (fabs(e) > speed)
    {
        e = (e < 0 ? -1 : 1) * speed;
    }

    if (rampTimer->Get() > 1.5f)
    {
        rampTimer->Stop();
    }

    float t = e * (1.0f / (fabs(rangeMin) + fabs(rangeMax)));
    output = t * pow(1 + rampTimer->Get(), 3);

    SmartDashboard::PutNumber("TBH Input", input);
    SmartDashboard::PutNumber("TBH Error", e);
    SmartDashboard::PutNumber("TBH Output", output);
}

float ErrorTimeSquared::GetTarget()
{
    return target;
}

void ErrorTimeSquared::SetTarget(float target)
{
    this->target = target;
}

float ErrorTimeSquared::GetInput()
{
    return input;
}

void ErrorTimeSquared::SetInput(float input)
{
    this->input = input;
}

float ErrorTimeSquared::GetOutput()
{
    Update();
    return output;
}

float ErrorTimeSquared::GetError()
{
    return input - target;
}