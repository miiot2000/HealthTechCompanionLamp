
/*
* This is the Companion Lamp
* This program is dependent on a pair of lamps
* The user will be able to adjust the colour, brigthness and temperature of one lamp and then being able to transfer all of that data into another lamp
* The lamp is designed to address social isolation among adults who work remotely
*/

#include "Adafruit_NeoPixel.h";
#include "RH_ASK.h";
#include "SPI.h";
Adafruit_NeoPixel strip(NUM_LEDS, 6, NEO_GRB + NEO_KHZ800); // Initialize NeoPixel object

// Define potentiometers in the analog pins to read its values
#define COLOR_POT A0 // Analog pin that adjusts colour like a colour wheel 
#define BRIGHTNESS_POT A1 // Analog pin that adjusts the brightness
#define NUM_PIXELS    24  //how many pixels total

// Define Touch Sensors in the digital pins. This wil be your input value
#define TOUCH_LEFT 2
#define TOUCH_RIGHT 3

// Define pin location of heating pads. The heating pad will act as your output value
#define HEATING_PAD_LEFT 4
#define HEATING_PAD_RIGHT 5

// Define pin location of the RF Transmitter
#define RF_TRANSMIT 10

// Define the maximum temperature of the heating pad
#define MAX_TEMPERATURE_CELSIUS 28

// Define the temperature increment value per loop iteration
#define TEMPERATURE_INCREMENT 0.1

// Define the cooling rate per loop iteration
#define COOLING_RATE 0.05

//Initalize colour, brightness, and temperature variables
int colorPot = 0;
int brightnessPot = 0;
double temperature = 0;

//Initialize the state of the heating pads whether they are on or off
boolean leftSideHeat = false;
boolean rightSideHeat = false;

// Making an instance of the RH_ASK driver
RH_ASK driver;

void setup() {
// // Initialize the NeoPixel Ring
//   strip.begin(); // Turn all LED on
//   strip.show(); // Turn all LEDs off

// Setting the touch sensor pins to input mode
pinMode (TOUCH_LEFT, INPUT);
pinMode (TOUCH_RIGHT, INPUT);

// Setting the heating pad pins to output mode
pinMode (HEATING_PAD_LEFT, OUTPUT);
pinMode (HEATING_PAD_RIGHT, OUTPUT);

// Initialize the RH_ASK Driver
driver.init();

// Setting the RF Transmit Pin
pinMode (RF_TRANSMIT, OUTPUT);

// Initialize all of the set values which includes the colour, brightness and temperature
colorPot = map (analogRead (COLOR_POT), 0, 1023, 0, NUM_PIXELS - 1);
brightnessPot = map (analogRead (BRIGHTNESS_POT), 0, 1023, 0, 255);
temperature = 0; 
}

void loop() {
  // Read the  potentiometer values
  colorPot = map (analogRead (COLOR_POT), 0, 1023, 0, NUM_PIXELS - 1);
  brightnessPot = map (analogRead (BRIGHTNESS_POT), 0, 1023, 0, 255);


  //Setting up the Neopixel Ring Colour Range and Brightness
  for (int = i = 0; i < NUM_PIXELS; i++) {
    if (i == colorPot) {
      pixels.setPixelColor (i, pixels.Color (255, 0, 0)); //RED
    }
    else {
      pixels.setPixelColor (i, pixels.Color (0, 0, 255)); //BLUE

    }
    pixels.setBrightness(brightnessPot);
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

// Prepare for the data values to be transmitted
byte data[5];
data[0] = colorPot & 0xFF;
data[1] = brightnessPot & 0xFF;
memcpy(&data[2], temperature, sizeof(temperature));

// Send out to transmitter
driver.send(data, sizeof(data));

// Wait for the transmission to complete
driver.waitPacketSent();

// Delay before the next transmission
delay(1000);

}


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
* Simple Receiver Code
* (TX out of Arduino is Digital Pin 1)
* (RX into Arduino is Digital Pin 0)
*/

#include "RH_ASK.h";
#include "SPI.h";

#define RF_RECIEVER 11

//Initalize colour, brightness, and temperature variables
int colorPot = 0;
int brightnessPot = 0;
double temperature = 0;
int incomingByte = 0;

// Making an instance of the RH_ASK driver
RH_ASK driver;


void setup(){
// Initialize driver
driver.init();

// Setting the RF Reciever Pin
pinMode (RF_RECIEVER, OUTPUT);

pixels.begin();
}
void loop() {
  // Read the potentiometer values
  int brightnessPotValue = analogRead(BRIGHTNESS_POT_PIN);
  int colorPotValue = analogRead(COLOR_POT_PIN);

  // Map the potentiometer values to the appropriate range
  brightness = map(brightnessPotValue, 0, 1023, 0, 255);
  colorIndex = map(colorPotValue, 0, 1023, 0, NUM_PIXELS - 1);

  // Read the temperature (temperature calculation code goes here)
  temperature += TEMPERATURE_INCREMENT;

  // Set the NeoPixel colors and brightness
  for (int i = 0; i < NUM_PIXELS;