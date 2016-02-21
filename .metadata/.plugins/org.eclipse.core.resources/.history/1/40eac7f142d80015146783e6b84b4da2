#ifndef TAKEBACKHALF_HPP
#define TAKEBACKHALF_HPP

#include <Schematic.hpp>

class TakeBackHalf
{
    private:
        float target;
        float input;
        float output;
        float speed;

        float rangeMin, rangeMax;

        Timer *timer;

        void Update();
    public:
        TakeBackHalf(float speed, float rangeMin, float rangeMax)
        {
            target = 0.0f;
            input = 0.0f;
            output = 0.0f;
            this->speed = speed;
            this->rangeMin = rangeMin;
            this->rangeMax = rangeMax;
            timer = new Timer();
        }

        void Enable();
        void Disable();

        float GetTarget();
        void SetTarget(float target);

        float GetInput();
        void SetInput(float input);

        float GetOutput();

        float GetError();
};

#endif
