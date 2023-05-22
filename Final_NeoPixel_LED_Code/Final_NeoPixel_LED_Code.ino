#include <Adafruit_NeoPixel.h>
#include <RH_ASK.h>
#include <SPI.h>

#define NUM_PIXELS 24
#define COLOR_POT A0
#define BRIGHTNESS_POT A1

Adafruit_NeoPixel strip(NUM_PIXELS, 6, NEO_GRB + NEO_KHZ800);
RH_ASK driver;
byte data[8];

void setup() {
  strip.begin();
  strip.show();

  pinMode(COLOR_POT, INPUT);
  pinMode(BRIGHTNESS_POT, INPUT);

  driver.init();
  Serial.begin(2400);
}

void loop() {
  int potColorNum = analogRead(COLOR_POT);
  int potBrightnessNum = analogRead(BRIGHTNESS_POT);

  int colorIndex = map(potColorNum, 0, 1023, 0, 255);
  int brightness = map(potBrightnessNum, 0, 1023, 0, 255);

  for (int i = 0; i < NUM_PIXELS; i++) {
    uint8_t red = map(colorIndex, 0, 255, 0, 255);
    uint8_t green = map(colorIndex, 0, 255, 255, 0);
    uint8_t blue = 0;
    uint32_t color = strip.Color(red, green, blue);
    strip.setPixelColor(i, color);
  }

  strip.setBrightness(brightness);
  strip.show();

  // Prepare the data packet to be transmitted
  data[0] = 0; // Counter (dummy value)
  data[1] = colorIndex;
  data[2] = brightness;
  data[3] = 0; // Temperature (dummy value)
  data[4] = 0; // Temperature (dummy value)

  // Send data packet
  driver.send(data, sizeof(data));
  driver.waitPacketSent();

  delay(10);
}

