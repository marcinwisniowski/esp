/**
 * ESP Tutorials
 * Module 02 - ADC basics
 * Basic example that uses potentiometer to simulate temperature sensor
 * @author Marcin F. Wiśniowski <marcin.wisniowski@databros.it>
 * @date 2020-06-14
 */

#include <Arduino.h>

// ESP32 Arduino pin definition may not have defined the LED_BUILTIN definition
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

#define ADC_POTENTIOMETER_PIN           A13

float_t setTemparature = 21.0;
float_t hysteresis = 1.5;
boolean running = false;

// ADC by default returns values form 0 to 4095
// This function converts that range into the desired temperature range in floating point type
float_t getTemperature(int16_t sensorRead) {
    float_t lowerBoundry = 5.0;
    float_t upperBoundry = 32.0;
    return lowerBoundry + (float_t)sensorRead * (upperBoundry - lowerBoundry) / 4095;
}

boolean engage(float_t target, float_t margin, float_t current, boolean state) {
    return ((!state && (current < target - margin)) || (state && (current < target + margin)));
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ADC_POTENTIOMETER_PIN, ANALOG);
}

void loop() {
    float_t temp;
    temp = getTemperature(analogRead(ADC_POTENTIOMETER_PIN));
    Serial.printf("Temperature: %4.2f C\n", temp);
    running = engage(setTemparature, histeresis, temp, running);
    if (running) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
    delay(250);
}