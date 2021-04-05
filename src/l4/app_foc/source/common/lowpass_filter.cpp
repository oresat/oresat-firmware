#include "lowpass_filter.h"

LowPassFilter::LowPassFilter(float time_constant)
    : Tf(time_constant)
    , y_prev(0.0f)
{
    //timestamp_prev = micros(); //ARDUINO_MAYBE
    timestamp_prev = time_usecs_t(); //CHIBIOS_MAYBE
}


float LowPassFilter::operator() (float x)
{
    //unsigned long timestamp = micros(); //ARDUINO_MAYBE
    unsigned long timestamp = time_usecs_t(); //CHIBIOS_MAYBE
    float dt = (timestamp - timestamp_prev)*1e-6f;

    if (dt < 0.0f || dt > 0.5f)
        dt = 1e-3f;

    float alpha = Tf/(Tf + dt);
    float y = alpha*y_prev + (1.0f - alpha)*x;

    y_prev = y;
    timestamp_prev = timestamp;
    return y;
}
