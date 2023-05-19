#include "Adafruit_NeoPixel.h"
#include "RH_ASK.h"

#define NUM_PIXELS 24 // how many pixels total
#define COLOR_POT A0 // Analog pin that adjusts color like a color wheel
#define BRIGHTNESS_POT A1 // Analog pin that adjusts the brightness
#define TOUCH_LEFT 2 // Define Touch Sensors in the digital pins. This will be your input value
#define TOUCH_RIGHT 3
#define HEATING_PAD_LEFT 4 // Define pin location of heating pads. The heating pad will act as your output value
#define HEATING_PAD_RIGHT 5
#define MAX_TEMPERATURE_CELSIUS 28 // Define the maximum temperature of the heating pad
#define TEMPERATURE_INCREMENT 0.1 // Define the temperature increment value per loop iteration
#define COOLING_RATE 0.05 // Define the cooling rate per loop iteration

Adafruit_NeoPixel strip(NUM_PIXELS, 6, NEO_GRB + NEO_KHZ800); // Initialize NeoPixel object

int potColorNum = 0; // Initialize variables to store the values of the potentiometer values
int potBrightnessNum = 0;
boolean leftSideHeat = false; // Initialize the state of the heating pads whether they are on or off
boolean rightSideHeat = false;
double temperature = 0; // Initialize variables to store the temperature values of the heating pads
byte counter;

void setup() {
  strip.begin(); // Initialize the NeoPixel Ring
  strip.show(); // Turn all LEDs off

  pinMode(TOUCH_LEFT, INPUT); // Setting the touch sensor pins to input mode
  pinMode(TOUCH_RIGHT, INPUT);
  pinMode(HEATING_PAD_LEFT, OUTPUT); // Setting the heating pad pins to output mode
  pinMode(HEATING_PAD_RIGHT, OUTPUT);

  Serial.begin(2400); // 2400 baud for the 434 model
  counter = 0;
}

void loop() {
  potColorNum = analogRead(COLOR_POT); // Read the potentiometer values
  potBrightnessNum = analogRead(BRIGHTNESS_POT);

  int colorIndex = map(potColorNum, 0, 1023, 0, NUM_PIXELS - 1); // Mapping the potentiometer values to the appropriate ranges
  int brightness = map(potBrightnessNum, 0, 1023, 0, 255);

  for (int i = 0; i < NUM_PIXELS; i++) {
    if (i == colorIndex) {
      strip.setPixelColor(i, strip.Color(255, 0, 0)); // RED
    } else {
      strip.setPixelColor(i, strip.Color(0, 0, 255)); // BLUE
    }
    strip.setBrightness(brightness);
  }

  strip.show(); // Update the NeoPixel Ring

  int touchSensorLeft = digitalRead(TOUCH_LEFT); // Reading the touch sensor values
  int touchSensorRight = digitalRead(TOUCH_RIGHT);

  if (touchSensorLeft == HIGH) { // Checking to see if the left sensor is being touched and adjusting temperature accordingly
    digitalWrite(HEATING_PAD_LEFT, HIGH);
    leftSideHeat = true;
    temperature += TEMPERATURE_INCREMENT;
  } else {
    digitalWrite(HEATING_PAD_LEFT, LOW);
    leftSideHeat = false;
  }

    // Checking to see if the right touch sensor is being touched and adjusting temperature accordingly
  if (touchSensorRight == HIGH) {
    digitalWrite(HEATING_PAD_RIGHT, HIGH);
    rightSideHeat = true;
    temperature += TEMPERATURE_INCREMENT;
  } else {
    digitalWrite(HEATING_PAD_RIGHT, LOW);
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

  // Limit the temperature to non-negative values
  if (temperature < 0) {
    temperature = 0;
  }

  // send out to transmitter
  Serial.print(counter);
  counter++;
  delay(10);
}

