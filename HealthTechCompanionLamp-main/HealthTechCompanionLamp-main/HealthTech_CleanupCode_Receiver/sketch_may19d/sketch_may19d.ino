#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;
byte data[8];

void setup() {
  Serial.begin(9600); // Initialize serial communication
  driver.init();
}

void loop() {
  if (driver.recv(data, sizeof(data))) {
    byte counter = data[0];
    int colorIndex = data[1];
    int brightness = data[2];
    int temperatureInt = (data[3] << 8) | data[4]; // Combine the higher and lower byte of temperature
    double temperature = temperatureInt / 10.0; // Convert temperature back to decimal value

    // Process the received data as needed
    Serial.print("Counter: ");
    Serial.println(counter);
    Serial.print("Color Index: ");
    Serial.println(colorIndex);
    Serial.print("Brightness: ");
    Serial.println(brightness);
    Serial.print("Temperature: ");
    Serial.println(temperature);
  }
}

