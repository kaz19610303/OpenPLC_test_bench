#include <stdlib.h>
extern "C" {
#include "openplc.h"
}
#include "Arduino.h"

//OpenPLC HAL for Spresense Extension

/******************PINOUT CONFIGURATION*******************
Digital In: 0, 1, 2, 4, 7           (%IX0.0 - %IX0.4)
Digital Out: 8, 10, 11, 12, 13      (%QX0.0 - %QX0.4)
Analog In: A0, A1, A2, A3, A4, A5   (%IW0 - %IW5)
Analog Out: 3, 5, 6, 9              (%QW0 - %QW3)
**********************************************************/

//Define the number of inputs and outputs for this board (mapping for the Arduino Uno)
#define NUM_DISCRETE_INPUT          5
#define NUM_ANALOG_INPUT            6
#define NUM_DISCRETE_OUTPUT         5
#define NUM_ANALOG_OUTPUT           4

//Create the I/O pin masks
uint8_t pinMask_DIN[] = {0, 1, 2, 4, 7};
uint8_t pinMask_AIN[] = {A0, A1, A2, A3, A4, A5};
uint8_t pinMask_DOUT[] = {8, 10, 11, 12, 13};
uint8_t pinMask_AOUT[] = {3, 5, 6, 9};

void hardwareInit()
{
    for (int i = 0; i < NUM_DISCRETE_INPUT; i++)
    {
		uint8_t pin = pinMask_DIN[i];
        pinMode(pin, INPUT);
    }
    
    for (int i = 0; i < NUM_ANALOG_INPUT; i++)
    {
		uint8_t pin = pinMask_AIN[i];
        pinMode(pin, INPUT);
    }
    
    for (int i = 0; i < NUM_DISCRETE_OUTPUT; i++)
    {
		uint8_t pin = pinMask_DOUT[i];
        pinMode(pin, OUTPUT);
    }

    for (int i = 0; i < NUM_ANALOG_OUTPUT; i++)
    {
		uint8_t pin = pinMask_AOUT[i];
        pinMode(pin, OUTPUT);
    }
}

void updateInputBuffers()
{
    for (int i = 0; i < NUM_DISCRETE_INPUT; i++)
    {
		uint8_t pin = pinMask_DIN[i];
        if (bool_input[i/8][i%8] != NULL) 
            *bool_input[i/8][i%8] = digitalRead(pin);
    }
    
    for (int i = 0; i < NUM_ANALOG_INPUT; i++)
    {
		uint8_t pin = pinMask_AIN[i];
        if (int_input[i] != NULL)
            *int_input[i] = (analogRead(pin) * 64);
    }
}

void updateOutputBuffers()
{
    for (int i = 0; i < NUM_DISCRETE_OUTPUT; i++)
    {
		uint8_t pin = pinMask_DOUT[i];
        if (bool_output[i/8][i%8] != NULL) 
            digitalWrite(pin, *bool_output[i/8][i%8]);
    }
    for (int i = 0; i < NUM_ANALOG_OUTPUT; i++)
    {
		uint8_t pin = pinMask_AOUT[i];
        if (int_output[i] != NULL) 
            analogWrite(pin, (*int_output[i] / 256));
    }
}
