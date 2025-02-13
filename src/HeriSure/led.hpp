/**
 * @file Led.hpp
 * @brief LED control implementation
 */

 #ifndef LED_H
 #define LED_H
 
 #include <Arduino.h>
 
 void led_init(void);
 void led_on(void);
 void led_off(void);
 void led_control(float temperature, float threshold);
 
 #endif
 