#include <RH_ASK.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 24 // Number of pixels in the LED ring
#define NEO_PIN 6 // Pin where the neopixel is connected
#define LED_BRIGHTNESS 50 // Adjust the brightness of the neopixel

Adafruit_NeoPixel strip(NUM_PIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);
RH_ASK driver;

byte data[8];
byte prevCounter = 0;
int prevColorIndex = 0;
int prevBrightness = 0;
double prevTemperature = 0;

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(LED_BRIGHTNESS);
  driver.init(); // Initialization of receiver pin is PIN 11
  Serial.begin(2400);
}

void loop() {
  if (driver.recv(data, sizeof(data))) {
    byte counter = data[0];
    int colorIndex = data[1];
    int brightness = data[2];
    int temperatureInt = ((data[3] << 8) | data[4]);
    double temperature = temperatureInt / 10.0;

    if (counter != prevCounter || colorIndex != prevColorIndex || brightness != prevBrightness || temperature != prevTemperature) {
      // Update the neopixel color and brightness
      int red = 0;
      int green = 0;
      int blue = 0;

      if (colorIndex < 1536) {
        red = 255;
        green = colorIndex;
      } else if (colorIndex < 3072) {
        red = 3071 - colorIndex;
        green = 255;
      } else if (colorIndex < 4608) {
        green = 255;
        blue = colorIndex - 3071;
      } else if (colorIndex < 6144) {
        green = 6143 - colorIndex;
        blue = 255;
      } else if (colorIndex < 7168) {
        red = colorIndex - 6143;
        blue = 255;
      } else {
        red = 255;
        blue = 7167 - colorIndex;
      }

      for (int i = 0; i < NUM_PIXELS; i++) {
        strip.setPixelColor(i, strip.Color(red, green, blue));
      }

      strip.setBrightness(brightness);
      strip.show();

      // Print received data
      Serial.print("Counter: ");
      Serial.println(counter);
      Serial.print("Color Index: ");
      Serial.println(colorIndex);
      Serial.print("Brightness: ");
      Serial.println(brightness);
      Serial.print("Temperature: ");
      Serial.println(temperature);
      Serial.println();

      // Update previous values
      prevCounter = counter;
      prevColorIndex = colorIndex;
      prevBrightness = brightness;
      prevTemperature = temperature;
    }
  }
}

