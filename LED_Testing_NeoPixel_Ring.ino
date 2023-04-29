#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 0
#define NUM_PIXELS 24

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // Initialize Neopixel library.
  pixels.show(); // Turn all pixels off.
}

void loop() {
  // Set all pixels to red.
  for(int i=0; i<NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Red color.
  }
  pixels.show(); // Update Neopixel ring.
  delay(1000); // Wait for 1 second.
  
  // Set all pixels to green.
  for(int i=0; i<NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Green color.
  }
  pixels.show(); // Update Neopixel ring.
  delay(1000); // Wait for 1 second.
  
  // Set all pixels to blue.
  for(int i=0; i<NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // Blue color.
  }
  pixels.show(); // Update Neopixel ring.
  delay(1000); // Wait for 1 second.
}
