#pragma once

#include <Schematic.hpp>

class ErrorTimeCubed
{
    private:
        float target;
        float input;
        float output;
        float rampMin;
        float rampMax;

        float rangeMin, rangeMax;

        Timer *timer;

        void Update();
    public:
        ErrorTimeCubed(const float& rampMin, const float& rampMax, const float& rangeMin, const float& rangeMax) :
            target(0.0f),
            input(0.0f),
            output(0.0f),
            rampMin(rampMin),
            rampMax(rampMax),
            rangeMin(rangeMin),
            rangeMax(rangeMax),
            timer(new Timer())
        {
        }

        void Enable();
        void Disable();

        float GetTarget();
        void SetTarget(const float& target);
        float GetInput();
        void SetInput(const float& input);
        float GetOutput();
        float GetError();
};
