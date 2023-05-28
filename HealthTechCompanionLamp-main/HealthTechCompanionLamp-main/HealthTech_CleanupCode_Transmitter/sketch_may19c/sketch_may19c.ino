#include <Adafruit_NeoPixel.h>
#include <RH_ASK.h>
#include <SPI.h>

/*
* Defining the variables 
*/
#define NUM_PIXELS 24 // The number of pixels within the LED ring
#define NEO_PIN 6 // The Pin where the neopixel will be running
#define COLOR_POT A0 // The analog pin where the color is being controlled
#define BRIGHTNESS_POT A1 // The analog pin where the brightness is being controlled 
#define TOUCH_LEFT 2 // The pin where the left touch sensor will be for the input of the left heating pad
#define TOUCH_RIGHT 3 // The pin where the right touch sensor will be the input for the right heating pad
#define HEATING_PAD_LEFT 4 // The pin location of the left heating pad 
#define HEATING_PAD_RIGHT 5 // The pin location of the right heating pad
#define MAX_TEMPERATURE_CELSIUS 40 // The maximum temperature of the heating pads
#define TEMPERATURE_INCREMENT 1 // The rate in which the temperature of the pads increase 
#define COOLING_RATE 0.05 // The rate of cooling of the heating pad

Adafruit_NeoPixel strip(NUM_PIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);
RH_ASK driver;

/*
* Initializing all variables
*/
int potColorNum = 0;
int potBrightnessNum = 0;
boolean leftSideHeat = false;
boolean rightSideHeat = false;
double temperature = 0;
byte counter;
byte data[8];

void setup() {
  strip.begin();
  strip.show();

  pinMode(TOUCH_LEFT, INPUT);
  pinMode(TOUCH_RIGHT, INPUT);
  pinMode(HEATING_PAD_LEFT, OUTPUT);
  pinMode(HEATING_PAD_RIGHT, OUTPUT);

  driver.init(); // Initalization of transmitter pin is PIN 12
  Serial.begin(2400);
  counter = 0;
}

void loop() {
  potColorNum = analogRead(COLOR_POT);
  potBrightnessNum = analogRead(BRIGHTNESS_POT);

  /*
  * Mapping the color and brightness to its appropriate ranges 
  */
  int colorIndex = map(potColorNum, 0, 1023, 0, 7167);
  int brightness = map(potBrightnessNum, 0, 1023, 0, 255);

  int red = 0;
  int green = 0;
  int blue = 0;

  /*
  * If statements serve to define the color wheel and ensure that the entire color wheel can be cycled within 28 turns as per the maximum amount of turns
  * the potentiometer can allow
  */
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
  /*
  * Updating the neopixel ring to the new color and brightness
  */
  strip.setBrightness(brightness);
  strip.show();

  /*
  * Reading the value of the touch sensors to manipulate the temperature of the heating pads
  */
  int touchSensorLeft = digitalRead(TOUCH_LEFT);
  int touchSensorRight = digitalRead(TOUCH_RIGHT);

  /*
  * If statements to turn on and off the heating pads
  */
  if (touchSensorLeft == HIGH || touchSensorRight == HIGH) {
    digitalWrite(HEATING_PAD_LEFT, HIGH);
    digitalWrite(HEATING_PAD_RIGHT, HIGH);
    
    leftSideHeat = true;
    rightSideHeat = true;
    temperature += TEMPERATURE_INCREMENT;
  } else {
    digitalWrite(HEATING_PAD_LEFT, LOW);
    digitalWrite(HEATING_PAD_RIGHT, LOW);

    leftSideHeat = false;
    rightSideHeat = false;

  }


  /*
  * Ensuring temperature cannot be raised above 28 celsius
  */
  if (temperature > MAX_TEMPERATURE_CELSIUS) {
    temperature = MAX_TEMPERATURE_CELSIUS;
  }

  /*
  * Cooling function of the heating pads to activate should the touch sensors not be touched
  */
  if (!leftSideHeat && !rightSideHeat) {
    temperature -= COOLING_RATE;
  }

  if (temperature < 0) {
    temperature = 0;
  }

  /*
  * Preparing for the data to be transferred 
  */
  data[0] = counter;
  data[1] = colorIndex;
  data[2] = brightness;
  int temperatureInt = temperature * 10;
  data[3] = temperatureInt >> 8;
  data[4] = temperatureInt & 0xFF;

/*
* Transmitting the data pack
*/
  driver.send(data, sizeof(data));
  driver.waitPacketSent();

  Serial.print("Counter: ");
  Serial.println(counter);
  Serial.print("Color Index: ");
  Serial.println(colorIndex);
  Serial.print("Brightness: ");
  Serial.println(brightness);
  Serial.print("Temperature: ");
  Serial.println(temperature);

  counter++;
  delay(10);
}



