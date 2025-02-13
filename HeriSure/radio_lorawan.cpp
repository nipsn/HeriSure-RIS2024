#include "service_lora.h"
/**
   @file radio.cpp
   @brief Abstracting the radio
*/

#include <Arduino.h>
#include "radio.hpp"
#include "credenciales.h"
#include "sensor.hpp"
#include <CayenneLPP.h>
#include "Led.hpp"

// Define the credentials as uint8_t arrays
uint8_t deveui[8] = OTAA_DEVEUI;
uint8_t appeui[8] = OTAA_APPEUI;
uint8_t appkey[16] = OTAA_APPKEY;

static bool connected = false;

static uint8_t uplink_payload[94];
static uint8_t uplink_cnt = 0;


static uint8_t fport = 1;

void recvCallback(SERVICE_LORA_RECEIVE_T* data) {
    if (data != NULL && data->BufferSize > 0) {
        Serial.println("Datos recibidos !!!");
        for (int i = 0; i < data->BufferSize; i++) {
            Serial.printf("0x%02X ", data->Buffer[i]); // Prints data in hexadecimal
        }
        Serial.println();
    }
}

// Callback to verify the join
void joinCallback(int32_t status) {
    if (status == 0) {
        Serial.println("¡Unión exitosa a LoRaWAN!");
    } else {
        Serial.println("Error al unirse a LoRaWAN.");
    }
}

// Callback to confirm the data send
void sendCallback(int32_t status) {
    if (status == 0) {
        Serial.println("Datos enviados exitosamente.");
    } else {
        Serial.println("Error al enviar datos.");
    }
}

bool radio_Init() {
    // OTAA credentials config
    if (api.lorawan.deui.set(deveui, 8)) {
        Serial.println("DevEUI configurado correctamente.");
    } else {
        Serial.println("Error al configurar DevEUI.");
        return false;
    }

    if (api.lorawan.appeui.set(appeui, 8)) {
        Serial.println("AppEUI configurado correctamente.");
    } else {
        Serial.println("Error al configurar AppEUI.");
        return false;
    }

    if (api.lorawan.appkey.set(appkey, 16)) {
        Serial.println("AppKey configurado correctamente.");
    } else {
        Serial.println("Error al configurar AppKey.");
        return false;
    }

    api.lorawan.band.set(OTAA_BAND);
    api.lorawan.deviceClass.set(RAK_LORA_CLASS_A);
    api.lorawan.njm.set(RAK_LORA_OTAA);
    api.lorawan.adr.set(true);  // Enable ADR

    // Callback registry
    api.lorawan.registerRecvCallback(recvCallback);
    api.lorawan.registerJoinCallback(joinCallback);
    api.lorawan.registerSendCallback(sendCallback);

    // Try to join the LoRaWAN network
    if (api.lorawan.join() != 0) {
        Serial.println("Fallo al intentar unirse a la red LoRaWAN.");
        return false;
    } else {
        Serial.println("Unión exitosa a la red LoRaWAN.");
        return true;
    }
}




// Send temperature and humidity data
void radio_sendData(float temperature, float humidity) {
    CayenneLPP lpp(51);

    // Add data to the payload
    lpp.addTemperature(1, temperature);
    lpp.addRelativeHumidity(2, humidity);

    // Send the payload
    int32_t result = api.lorawan.send(7, lpp.getBuffer(), lpp.getSize(), false);

    // Verify success
    if (result == 0) {
        Serial.println("Datos enviados a TTN exitosamente.");
    } else {
        Serial.print("Error al enviar datos a TTN. Código de error: ");
        Serial.println(result);
    }
}




