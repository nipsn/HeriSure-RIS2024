/**
   @file temperature.hpp
   @brief Abstracting a temperature sensor
**/

#ifndef SENSOR_H
#define SENSOR_H



void sensor_init(void);

float temperature_Read(void);
float humidify_Read(void);

#endif



