#include <Arduino.h>
#include "sensor.hpp"
#include "Led.hpp"
#include "radio.hpp"
#include "credentials.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Inicializando sistema...");

    led_init();       // LED Startup
    sensor_init();    // Sensor Startup

    // LoRaWAN Startup
    if (radio_Init()) {
        Serial.println("Conexión a TTN exitosa.");
    } else {
        Serial.println("Error al conectar con TTN.");
    }

    Serial.println("Sistema Iniciado");
}

void loop() {
    float temperature = temperature_Read();
    float humidity = humidify_Read();
    float threshold = 24.0;

    led_control(temperature, threshold);  // LED Control

    // Show data in serial monitor
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humedad: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Send data to TTN
    radio_sendData(temperature, humidity);

    delay(120000);  // Envía los datos cada dos minutos
}
