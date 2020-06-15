/**
 * ESP Tutorials
 * Module 05 - I2C Sensors: BMP280
 * Basic example how to read data from the single sensor connected tot the i2c bus
 * @author Marcin F. Wiśniowski <marcin.wisniowski@databros.it>
 * @date 2020-06-14
 */

#include <Arduino.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme280;
Adafruit_Sensor *tempSensor = bme280.getTemperatureSensor();
Adafruit_Sensor *pressureSensor = bme280.getPressureSensor();
Adafruit_Sensor *humiditySensor = bme280.getHumiditySensor();

void setup() {
    Serial.begin(115200);

    if ( !bme280.begin(0x76) ) {
        Serial.println(F("Could not find a valid BME280 sensor!"));
        while (1) delay(100);
    }

    bme280.setSampling(
            Adafruit_BME280::MODE_NORMAL,                                       // Operating Mode.
            Adafruit_BME280::SAMPLING_X2,                                       // Temp. oversampling
            Adafruit_BME280::SAMPLING_X16,                                      // Pressure oversampling
            Adafruit_BME280::SAMPLING_X2,                                       // Humidity oversampling
            Adafruit_BME280::FILTER_X16,                                        // Filtering
            Adafruit_BME280::STANDBY_MS_500                                     // Standby time
    );

    tempSensor->printSensorDetails();
    pressureSensor->printSensorDetails();
    humiditySensor->printSensorDetails();
}

void loop() {
    sensors_event_t eventTemp, eventPressure, eventHumidity;
    tempSensor->getEvent(&eventTemp);
    pressureSensor->getEvent(&eventPressure);
    humiditySensor->getEvent(&eventHumidity);

    Serial.printf_P(PSTR("Temperature: %2.2f C\n"), eventTemp.temperature);
    Serial.printf_P(PSTR("Pressure: %10.2f hPa\n"), eventPressure.pressure);
    Serial.printf_P(PSTR("Humidity: %8.2f %%\n"), eventHumidity.relative_humidity);

    Serial.println();
    delay(1000);
}