// SPDX-FileCopyrightText: 2018 Erin St. Blaine for Adafruit Industries
//
// SPDX-License-Identifier: MIT

// Code by Erin St. Blaine for Adafruit Industries
// Color Touch Pendant Tutorial: https://learn.adafruit.com/color-touch-pendant-necklace/introduction
// Two neopixel rings connected on pin 1 will cycle through gradient colors when the pendant is touched.  For Gemma M0.

/*
* This 
*/

#include "Adafruit_NeoPixel.h";
#include "RH_ASK.h";
Adafruit_NeoPixel strip(NUM_LEDS, 6, NEO_GRB + NEO_KHZ800); // Initialize NeoPixel object

// Define potentiometers in the analog pins to read its values
#define COLOR_POT A0 // Analog pin that adjusts colour like a colour wheel 
#define BRIGHTNESS_POT A1 // Analog pin that adjusts the brightness
#define NUM_LEDS    24  //how many pixels total

// Define Touch Sensors in the digital pins. This wil be your input value
#define TOUCH_LEFT 2
#define TOUCH_RIGHT 3

// Define pin location of heating pads. The heating pad will act as your output value
#define HEATING_PAD_LEFT 4
#define HEATING_PAD_RIGHT 5

// Define the maximum temperature of the heating pad
#define MAX_TEMPERATURE_CELSIUS 28

// Define the temperature increment value per loop iteration
#define TEMPERATURE_INCREMENT 0.1

// Define the cooling rate per loop iteration
#define COOLING_RATE 0.05

//Initalize variables to store the values of the potentiometer values
int potColorNum = 0;
int potBrightnessNum = 0;

//Initialize the state of the heating pads whether they are on or off
boolean leftSideHeat = false;
boolean rightSideHeat = false;

// Initialize variables to store the temperature values of the heating pads
double temperature = 0; 

byte counter;

    

// // Calibrating your capacitive touch sensitivity: Change this variable to something between your capacitive touch serial readouts for on and off
// int touch = 650;    

// long oldState = 0;

// // set up capacitive touch button using the FreeTouch library
// Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(CAPTOUCH_PIN, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);


// TBlendType    currentBlending;
// CRGBPalette16 currentPalette;


void setup() {
// Initialize the NeoPixel Ring
  strip.begin(); // Turn all LED on
  strip.show(); // Turn all LEDs off

// Setting the touch sensor pins to input mode
pinMode (TOUCH_LEFT, INPUT);
pinMode (TOUCH_RIGHT, INPUT);

// Setting the heating pad pins to output mode
pinMode (HEATING_PAD_LEFT, OUTPUT);
pinMode (HEATING_PAD_RIGHT, OUTPUT);

//2400 baud for the 434 model
Serial.begin(2400);
counter = 0;

}

void loop() {
  // Read the  potentiometer values
  potColorNum = analogRead (COLOR_POT);
  potBrightnessNum = analogRead (BRIGHTNESS_POT);

  // Mapping the potentiometer values to the appropriate ranges
  int colorIndex = map (potColorNum, 0, 1023, 0, NUM_PIXELS - 1);
  int brightness = map (potBrightnessNum, 0, 1023, 0, 255);

  //Setting up the Neopixel Ring Colour Range and Brightness
  for (int = i = 0; i < NUM_PIXELS; i++) {
    if (i == colorIndex) {
      pixels.setPixelColor (i, pixels.Color (255, 0, 0)); //RED
    }
    else {
      pixels.setPixelColor (i, pixels.Color (0, 0, 255)); //BLUE

    }
    pixels.setBrightness(brigthness);
  }

  // Update the Neopixel Ring
  pixel.show();

  // Reading the touch sensor values 
  touchSensorLeft = digitalRead (TOUCH_LEFT);
  touchSensorRight = digitalRead (TOUCH_RIGHT);

  // Checking to see if the left sensor is being touched and adjusting temperature accordingly 
  if (touchSensorLeft == HIGH) {
    digitalWrite (HEATING_PAD_LEFT, HIGH);
     leftSideHeat = true;

     temperature += TEMPERATURE_INCREMENT;
  } 
  else {
    digitalWrite (HEATING_PAD_LEFT, LOW);
    leftSideHeat = false;
  }

// Checking to see if the right touch sensor is being touched and adjusting temperature accordingly
if (touchSensorRight == HIGH) {
    digitalWrite (HEATING_PAD_RIGHT, HIGH);
     rightSideHeat = true;

     temperature += TEMPERATURE_INCREMENT;
  } 
  else {
    digitalWrite (HEATING_PAD_RIGHT, LOW);
    rightSideHeat = false;
  }

// Limiting the temperature of the heating pad to its maximum value
if (temperature > MAX_TEMPERATURE_CELSIUS) {
  temperature = MAX_TEMPERATURE_CELSIUS;
}

// Cooling the heating pad if no touch sensor is being touched
if (!leftSideHeat && !rightSideHeat) {
  temperature -= COOLING_RATE;
}

// Limit the temperature to non negative values
if (temperature < 0) {
  temperature = 0;
}

//send out to transmitter
Serial.print(counter);
counter++;
delay(10);

}


// -------------------------------------------------------------------

/*
* Simple Receiver Code
* (TX out of Arduino is Digital Pin 1)
* (RX into Arduino is Digital Pin 0)
*/
int incomingByte = 0;
void setup(){
//2400 baud for the 434 model
Serial.begin(2400);
}
void loop(){
// read in values, debug to computer
if (Serial.available() > 0) {
incomingByte = Serial.read();
Serial.println(incomingByte, DEC);
}
incomingByte = 0;
}