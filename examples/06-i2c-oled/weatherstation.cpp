
/**
 * ESP Tutorials
 * Module 06 - Weather Station
 * Basic example how to fetch data from I2CS sensor and display it on OLED display
 * @author Marcin F. Wiśniowski <marcin.wisniowski@databros.it>
 * @date 2020-06-15
 */

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>

#define OLED_SCREEN_WIDTH               128     // OLED display width, in pixels
#define OLED_SCREEN_HEIGHT              64      // OLED display height, in pixels
#define OLED_RESET_PIN                  -1      // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS                0x3C    // Generic address for 128x64 display

#define SENSOR_I2C_ADDRESS              0x76    // Generic address for BME280

Adafruit_BME280 bme280;
Adafruit_Sensor *tempSensor = bme280.getTemperatureSensor();
Adafruit_Sensor *pressureSensor = bme280.getPressureSensor();
Adafruit_Sensor *humiditySensor = bme280.getHumiditySensor();

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

const unsigned char logo [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x3f, 0xf0, 0x00, 0x70, 0x7f, 0xff, 0x07, 0x00, 0x7f, 0xc0, 0xff, 0x00, 0x0f, 0xc0, 0x07, 0xc0,
        0x3f, 0xfc, 0x00, 0x70, 0x7f, 0xff, 0x07, 0x00, 0x7f, 0xf0, 0xff, 0xc0, 0x3f, 0xf0, 0x1f, 0xf0,
        0x3f, 0xfe, 0x00, 0xf8, 0x3f, 0xfe, 0x0f, 0x80, 0x7f, 0xf8, 0xff, 0xe0, 0x7f, 0xf8, 0x3f, 0xf8,
        0x38, 0x1f, 0x00, 0xf8, 0x01, 0xc0, 0x0f, 0x80, 0x70, 0x3c, 0xe0, 0xf0, 0xf0, 0x3c, 0x38, 0x30,
        0x38, 0x07, 0x81, 0xdc, 0x01, 0xc0, 0x1d, 0xc0, 0x70, 0x1c, 0xe0, 0x71, 0xe0, 0x1e, 0x70, 0x00,
        0x38, 0x03, 0x81, 0xdc, 0x01, 0xc0, 0x1d, 0xc0, 0x70, 0x1c, 0xe0, 0x71, 0xc0, 0x0e, 0x70, 0x00,
        0x38, 0x03, 0xc3, 0x8e, 0x01, 0xc0, 0x38, 0xe0, 0x70, 0x3c, 0xe0, 0x71, 0xc0, 0x0e, 0x3c, 0x00,
        0x38, 0x01, 0xc3, 0x8e, 0x01, 0xc0, 0x38, 0xe0, 0x7f, 0xf8, 0xe0, 0xf3, 0x80, 0x07, 0x3f, 0x00,
        0x38, 0x01, 0xc3, 0x06, 0x01, 0xc0, 0x30, 0x60, 0x7f, 0xe0, 0xff, 0xe3, 0x80, 0x07, 0x0f, 0xc0,
        0x38, 0x01, 0xc7, 0x07, 0x01, 0xc0, 0x70, 0x70, 0x7f, 0xf8, 0xff, 0xc3, 0x80, 0x07, 0x03, 0xe0,
        0x38, 0x01, 0xc6, 0x03, 0x01, 0xc0, 0x60, 0x30, 0x70, 0x3c, 0xff, 0x03, 0x80, 0x07, 0x00, 0xf0,
        0x38, 0x03, 0xc7, 0xff, 0x01, 0xc0, 0x7f, 0xf0, 0x70, 0x1c, 0xe7, 0x81, 0xc0, 0x0e, 0x00, 0x78,
        0x38, 0x03, 0x8f, 0xff, 0x81, 0xc0, 0xff, 0xf8, 0x70, 0x1c, 0xe3, 0xc1, 0xc0, 0x0e, 0x00, 0x38,
        0x38, 0x07, 0x8f, 0xff, 0x81, 0xc0, 0xff, 0xf8, 0x70, 0x1c, 0xe1, 0xe1, 0xe0, 0x1e, 0x00, 0x38,
        0x38, 0x1f, 0x1c, 0x01, 0xc1, 0xc1, 0xc0, 0x1c, 0x70, 0x3c, 0xe0, 0xf0, 0xf0, 0x3c, 0x30, 0x70,
        0x3f, 0xfe, 0x1c, 0x01, 0xc1, 0xc1, 0xc0, 0x1c, 0x7f, 0xf8, 0xe0, 0x78, 0x7f, 0xf8, 0x7f, 0xf0,
        0x3f, 0xfc, 0x38, 0x00, 0xe1, 0xc3, 0x80, 0x0e, 0x7f, 0xf0, 0xe0, 0x38, 0x3f, 0xf0, 0x3f, 0xe0,
        0x3f, 0xf0, 0x38, 0x00, 0xe1, 0xc3, 0x80, 0x0e, 0x7f, 0xc0, 0xe0, 0x38, 0x0f, 0xc0, 0x0f, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x13, 0x26, 0x4c, 0x88, 0x13, 0x22, 0x26, 0x44, 0x09, 0x91, 0x36, 0x4c, 0x13, 0x26, 0x4d, 0x98,
        0x29, 0x52, 0xa5, 0x54, 0x29, 0x55, 0x52, 0xaa, 0x14, 0xaa, 0x92, 0xa4, 0x29, 0x52, 0xa4, 0x88,
        0x29, 0x52, 0xa5, 0x54, 0x29, 0x55, 0x52, 0xaa, 0x14, 0xaa, 0x92, 0xa4, 0x29, 0x52, 0xa4, 0x88,
        0x29, 0x52, 0xa5, 0x54, 0x29, 0x55, 0x52, 0xaa, 0x14, 0xaa, 0x92, 0xa4, 0x29, 0x52, 0xa4, 0x88,
        0x11, 0x22, 0x44, 0x88, 0x11, 0x22, 0x22, 0x44, 0x08, 0x91, 0x12, 0x44, 0x11, 0x22, 0x44, 0x88,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void updateDisplayValues(float_t temperature, float_t humidity, float_t pressure) {
    display.clearDisplay();
    display.cp437(true);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print("Temp");
    display.setCursor(64, display.getCursorY());
    display.print("Humidity");
    display.setCursor(0, 32);
    display.print("Pressure");
    display.setTextSize(2);
    display.setCursor(0, 10);
    display.printf("%2.0f%cC", temperature, 0xf8);
    display.setCursor(64, display.getCursorY());
    display.printf("%2.0f%%", humidity);
    display.setCursor(0, 44);
    display.printf("%6.1fhPa", pressure);
    display.display();
}

void setup() {
    Serial.begin(115200);

    if ( !bme280.begin(SENSOR_I2C_ADDRESS) ) {
        Serial.println(F("Could not find a valid BME280 sensor!"));
        while (1) delay(100);
    }

    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
        Serial.println(F("Could not find a valid SSD1306 display!"));
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

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.drawBitmap(0, 16,  logo, 128, 32, WHITE);               // Draw Logo as splash screen;
    display.display();
    delay(2000);
}

void loop() {
    sensors_event_t eventTemp, eventPressure, eventHumidity;
    tempSensor->getEvent(&eventTemp);
    pressureSensor->getEvent(&eventPressure);
    humiditySensor->getEvent(&eventHumidity);
    updateDisplayValues(eventTemp.temperature, eventHumidity.relative_humidity, eventPressure.pressure);
    delay(1000);
}
