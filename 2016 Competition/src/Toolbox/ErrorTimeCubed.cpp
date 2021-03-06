#include <Toolbox/ErrorTimeCubed.hpp>

void ErrorTimeCubed::Enable()
{
    timer->Reset();
    timer->Start();
}

void ErrorTimeCubed::Disable()
{
    timer->Stop();
}

void ErrorTimeCubed::Update()
{
    // Gets the current error.
    float e = GetError();

    // Keeps the speed from going to fast.
    if (e < rampMax)
    {
        e = rampMax;
    }

    // Keeps the speed from going to slow.
    if (e < rampMin)
    {
        e *= rampMin * 2.0f;
    }

    // Calculated the output.
    float t = e * (1.0f / (fabs(rangeMin) + fabs(rangeMax)));
    output = t * pow(1 + timer->Get(), 3);
}

float ErrorTimeCubed::GetTarget()
{
    return target;
}

void ErrorTimeCubed::SetTarget(const float& target)
{
    this->target = target;
}

float ErrorTimeCubed::GetInput()
{
    return input;
}

void ErrorTimeCubed::SetInput(const float& input)
{
    this->input = input;
}

float ErrorTimeCubed::GetOutput()
{
    Update();
    return output;
}

float ErrorTimeCubed::GetError()
{
    return input - target;
}
