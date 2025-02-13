#include "temperature.hpp"
#include "rak1901.h"
#include <Arduino.h>

rak1901 rak1901;


void temperature_init(void)
{
    // begin for I2C
    Wire.begin();
}

float temperature_read(void)
{
    float temp = 0.0;
    if (rak1901.update()) {
        temp = rak1901.temperature();
    }
    return temp;
}
