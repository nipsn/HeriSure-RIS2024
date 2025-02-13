/**
 * @file Led.cpp
 * @brief LED control implementation
 */

 #include "Led.hpp"

 // LED initialization. Sets pin as output
 void led_init(void) {
     pinMode(LED_BUILTIN, OUTPUT);
     digitalWrite(LED_BUILTIN, LOW); // Makes sure it starts off
 }
 
 // Turn on LED
 void led_on(void) {
     digitalWrite(LED_BUILTIN, HIGH);
 }
 
 // Turn off LED
 void led_off(void) {
     digitalWrite(LED_BUILTIN, LOW);
 }
 
 // Control the LED based on the temperature and the threshold
 void led_control(float temperature, float threshold) {
     if (temperature > threshold) {
         led_on();
     } else {
         led_off();
     }
 }
 