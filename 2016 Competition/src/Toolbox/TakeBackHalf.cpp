#include <Toolbox/TakeBackHalf.hpp>

void TakeBackHalf::Enable()
{
    timer->Reset();
    timer->Start();
}

void TakeBackHalf::Disable()
{
    timer->Stop();
}

void TakeBackHalf::Update()
{
    float gain = 1.2f;
    float e = GetError();
    float t = e * (1.0f / (fabs(rangeMin) + fabs(rangeMax)));
    output = t * pow(1 + timer->Get(), 3); // * fabs(speed);

    SmartDashboard::PutNumber("TBH Input", input);
    SmartDashboard::PutNumber("TBH Error", e);
    SmartDashboard::PutNumber("TBH Output", output);
}

float TakeBackHalf::GetTarget()
{
    return target;
}

void TakeBackHalf::SetTarget(float target)
{
    this->target = target;
}

float TakeBackHalf::GetInput()
{
    return input;
}

void TakeBackHalf::SetInput(float input)
{
    this->input = input;
}

float TakeBackHalf::GetOutput()
{
    Update();
    return output;
}

float TakeBackHalf::GetError()
{
    return input - target;
}
