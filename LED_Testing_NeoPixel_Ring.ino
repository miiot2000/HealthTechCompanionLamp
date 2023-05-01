// SPDX-FileCopyrightText: 2018 Erin St. Blaine for Adafruit Industries
//
// SPDX-License-Identifier: MIT

// Code by Erin St. Blaine for Adafruit Industries
// Color Touch Pendant Tutorial: https://learn.adafruit.com/color-touch-pendant-necklace/introduction
// Two neopixel rings connected on pin 1 will cycle through gradient colors when the pendant is touched.  For Gemma M0.

#include "Adafruit_NeoPixel.h";

#define CAPTOUCH_PIN 0  //capacitive touch pin
#define TOUCH_FFWD 2  // Digital pin that cycles colour wheel forward
#define TOUCH_BCKWD 3 // Digital pin that cycles colour wheel backward
#define NUM_LEDS    24  //how many pixels total

Adafruit_NeoPixel strip(NUM_LEDS, 6, NEO_GRB + NEO_KHZ800); // Initialize NeoPixel object

// // These variables will affect the way the gradient animation looks.  Feel free to mess with them.
// int SPEEDO = 10;          
// int STEPS = 50;         
// int HUE = 0;            
// int SATURATION = 255;  
// int COLORCHANGE = 50;        
// int BRIGHTNESS = 110;     

int current_colour = 0; // Current colour of lamp
unsigned long last_time_touched = 0; // Time lamp was last touched
const unsigned long touch_debounce_delay = 50; // Delay to debounce touch input

int current_brightness = 50; // Setting the default brighness of LED to 50%
const int brightness_increment = 10; // Brightness level increment, it'll either increase or decrease by 10% every adjustment

// // Calibrating your capacitive touch sensitivity: Change this variable to something between your capacitive touch serial readouts for on and off
// int touch = 650;    

// long oldState = 0;

// // set up capacitive touch button using the FreeTouch library
// Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(CAPTOUCH_PIN, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);


// TBlendType    currentBlending;
// CRGBPalette16 currentPalette;


void setup() {
  // Serial.begin(115200);

  // if (! qt_1.begin())  
  //  Serial.println("Failed to begin qt on pin A1");
  //  FastLED.addLeds<WS2812, NEOPIXEL_PIN, COLOR_ORDER>(leds, NUM_LEDS);  // Set up neopixels with FastLED
  //  FastLED.setBrightness(BRIGHTNESS); // set global brightness
  //  FastLED.setMaxPowerInVoltsAndMilliamps(3,350);  //Constrain FastLED's power usage
  //  strip.begin();
  //  strip.end();

  strip.begin(); // Initialize the NeoPixel Ring
  strip.show(); // Turn all LEDs off
}

void loop() {
  //Checking to see if the forward sensor is being touched
  if (digitalRead(TOUCH_FFWD) == HIGH && millis() - last_time_touched > touch_debounce_delay) { //We're going to be using milliseconds to measure time 
  // Cycle Colur Wheel Forward
  current_colour = (current_colour + 1) % 256;
  // Set all LEDs to the new colour
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Colour(current_colour, 0, 0)); // This sets red as the default colour
  }
  strip.show(); // Update the NeoPixel ring colour
  strip.setBrightness(current_brightness * 2.55) //Convert brightness between 0 and 255
  last_time_touched = millis(); // Update the last time sensor was touched. Milliseconds is the measurement

}
//Checking to see if the backward sensor is being touched
 if (digitalRead(TOUCH_BCKWD)) == HIGH && millis() - last_time_touched > touch_debounce_delay) {
   // Cycle Colour Wheel Backward 
   current_colour = (current_colour + 255) % 256;
   // Set all LEDs to the new colour
    for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Colour(current_colour, 0, 0)); // This sets red as the default colour
  }
  strip.show(); // Update the NeoPixel ring colour
  strip.setBrightness(current_brightness * 2.55) //Convert brightness between 0 and 255
  last_time_touched = millis(); // Update the last time sensor was touched. Milliseconds is the measurement
 }
 //Checking to see if the brightness should be adjusted on the FFWD Strip
 if (millis() - last_time_touched > 5000) { // Setting is adjusted to the LED waiting 5 seconds before seeing if the LED needs to adjust its brightness
 int touch_value = touchRead(TOUCH_FFWD);
 int new_brightness = map (touch_value, 0, 1023, 0, 100); // Mapping the touch input to specific sensor
 new_brightness = new_brightness / brightness_increment * brightness_increment; // Round brightness to nearest increment
 if (new_brightness != current_brightness) { // When brightness is changed
    strip.setBrightness(current_brightness * 2.55); // Convert brightness to a value between 0 and 255
    strip.show(); //Update NeoPixel Ring
    }
 }
//Checking to see if the brightness should be adjusted on the BCKWD Strip
 if (millis() - last_time_touched > 5000) { // Setting is adjusted to the LED waiting 5 seconds before seeing if the LED needs to adjust its brightness
 int touch_value = touchRead(TOUCH_BCKWD);
 int new_brightness = map (touch_value, 0, 1023, 0, 100); // Mapping the touch input to specific sensor
 new_brightness = new_brightness / brightness_increment * brightness_increment; // Round brightness to nearest increment
 if (new_brightness != current_brightness) { // When brightness is changed
    strip.setBrightness(current_brightness * 2.55); // Convert brightness to a value between 0 and 255
    strip.show(); //Update NeoPixel Ring
 }
 }
}
