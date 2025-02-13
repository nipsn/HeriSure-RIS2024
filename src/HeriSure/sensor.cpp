#include "sensor.hpp"
#include <Adafruit_SHTC3.h>

Adafruit_SHTC3 shtc3;

void sensor_init(void){
    if(!shtc3.begin()){
        Serial.println("Falla al inicializar el sensor SHTC3!!");
        while(1) delay(10);
    }
    Serial.println("Sensor SHTC3 iniciado con éxito :) !!");
}   

float temperature_Read(void){
    sensors_event_t humidity, temp;
    shtc3.getEvent(&humidity, &temp);
    return temp.temperature;
}

float humidify_Read(void){
    sensors_event_t humidity, temp;
    shtc3.getEvent(&humidity, &temp);
    return humidity.relative_humidity;
}