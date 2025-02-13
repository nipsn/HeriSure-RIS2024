/**
   @file radio.hpp
   @brief Abstractiong the radio modem
**/
#ifndef RADIO_H
#define RADIO_H

bool radio_Init(void);
void radio_sendData(float temperature, float humidity);  // Agregado para el envío de datos
void radio_Run(void);

void radio_startPayload(uint8_t data, uint8_t port);
bool radio_sendPayload(void);




void Alerta();
void CAYENNE_LPP();

int16_t radio_downlinrRead(void);

#define OTAA_BAND  (RAK_REGION_EU868)



#endif
