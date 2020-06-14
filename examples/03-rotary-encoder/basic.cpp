/**
 * ESP Tutorials
 * Module 02 - RotaryEncoder Basics
 * Basic usage of Rotary Encoder. In this exercise it is used rotary encoder with 20 CPR
 * @author Marcin F. Wiśniowski <marcin.wisniowski@databros.it>
 * @date 2020-06-08
 */
#include <Arduino.h>
#include <ESPRotary.h>


#define ENC_CLK                         5   // GPIO5
#define ENC_DT                          4   // GPIO4
#define ENC_SW                          2   // GPIO2

#define ENC_SSN                         4   // Steps per notch

ESPRotary encoder = ESPRotary(ENC_CLK, ENC_DT, ENC_SSN, 176, 330);

// on change
void rotate(ESPRotary& r) {
    Serial.print("Set temperature: ");
    Serial.println(r.getPosition() / 10.0);
}

void setup() {
    Serial.begin(115200);
    //encoder = ESPRotary(ENC_CLK, ENC_DT, ENC_SSN, 0, 100);
    Serial.println("Basic Encoder Test:");
    encoder.setChangedHandler(rotate);
}

void loop() {
    encoder.loop();
}
