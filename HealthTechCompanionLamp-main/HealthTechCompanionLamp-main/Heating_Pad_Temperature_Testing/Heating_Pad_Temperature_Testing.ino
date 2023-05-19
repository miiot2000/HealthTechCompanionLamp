#include "Adafruit_NeoPixel.h";

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

// Initialize Temperature
double temperature = 0;

//Initialize the state of the heating pads whether they are on or off
boolean leftSideHeat = false;
boolean rightSideHeat = false;

void setup() {
  // put your setup code here, to run once:
// Setting the touch sensor pins to input mode
pinMode (TOUCH_LEFT, INPUT);
pinMode (TOUCH_RIGHT, INPUT);

// Setting the heating pad pins to output mode
pinMode (HEATING_PAD_LEFT, OUTPUT);
pinMode (HEATING_PAD_RIGHT, OUTPUT);

temperature = 0; 
 int touchSensorLeft = digitalRead (TOUCH_LEFT);
 int touchSensorRight = digitalRead (TOUCH_RIGHT);


}

void loop() {
  // put your main code here, to run repeatedly:
// Reading the touch sensor values 
  int touchSensorLeft = digitalRead (TOUCH_LEFT);
  int touchSensorRight = digitalRead (TOUCH_RIGHT);

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
}
