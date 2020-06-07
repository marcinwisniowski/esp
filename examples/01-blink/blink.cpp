/**
 * ESP Tutorials
 * Module 01 - Blink
 * Basic Example used to blink the LED.
 * @author Marcin F. Wiśniowski <marcin.wisniowski@databros.it>
 * @date 2020-06-06
 */
#include <Arduino.h>

// ESP32 Arduino pin definition may not have defined the LED_BUILTIN definition
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

// Note that ESP32 and ESP01 has different connection on LED. ESP01 emits light on low
void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1900);
}
