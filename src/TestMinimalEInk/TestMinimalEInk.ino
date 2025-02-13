/* Arduino version */
#include "app.h"

#define PAUSE 100

uint32_t counter = 0;
bool has_1901 = true;

void setup()
{
    LED_Init();
    Serial.begin(115200);
    temperature_init();
    init_rak14000();

    set_temp_rak14000(12.4);
    refresh_rak14000();
}

void loop()
{
    // float temper;

    // temper = temperature_read();
    // // Serial.print(temper);
    // // Serial.println(" °C");

    // if (temper > 20.0)
    // {
    //     LED_On();
    // }
    // else
    // {
    //     LED_Off();
    // }

    // set_temp_rak14000(temper);
    // refresh_rak14000();

    // delay(10000);
}