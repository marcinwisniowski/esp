/**
 * ESP Tutorials
 * Module 04 - I2C Buss Basics
 * Basic I2C bus scanner, it supports basic implementation of the bus with 7bit only addresses.
 * @author Marcin F. Wiśniowski <marcin.wisniowski@databros.it>
 * @date 2020-06-12
 */
#include <Arduino.h>
#include <Wire.h>

// Prints a binary number with leading zeros
#define PRINT_7BIT(Address) for (uint8_t i = 0x40; i; i >>= 1) Serial.write(Address & i ? '1' : '0');

void setup() {
    Serial.begin(115200);
    Wire.begin();
    Serial.println("I2C Scanner");
}

void loop() {
    uint8_t error, address, devices = 0;

    Serial.println("Scanning...");
    Serial.println("---------------------------------------------");
    // Scan only 7-bit addresses and omit the reserved ones
    for(address = 0x03; address < 0x78; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (!error) {
            Serial.print("I2C device found at address: 0x");
            Serial.print(address, HEX);
            Serial.print(" | ");
            PRINT_7BIT(address);
            Serial.print(" |\n");
            devices++;
        } else if (error == 4) {
            Serial.print("Unknown error at address: 0x");
            Serial.println(address,HEX);
        }
    }
    Serial.println("=============================================");
    Serial.printf("Found %d I2C devices.\n\n", devices);
    delay(5000);
}
