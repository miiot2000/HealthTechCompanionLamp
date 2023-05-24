#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

byte data[8];
int colorIndex = 0;
int brightness = 0;
double temperature = 0;

void setup() {
  Serial.begin(2400);
  if (!driver.init())
    Serial.println("Receiver initialization failed");
}

void loop() {
  if (driver.recv(data, sizeof(data))) {
    byte counter = data[0];
    colorIndex = data[1];
    brightness = data[2];
    int temperatureInt = (data[3] << 8) | data[4];
    temperature = temperatureInt / 10.0;

    Serial.print("Received Counter: ");
    Serial.println(counter);
    Serial.print("Received Color Index: ");
    Serial.println(colorIndex);
    Serial.print("Received Brightness: ");
    Serial.println(brightness);
    Serial.print("Received Temperature: ");
    Serial.println(temperature);
  }
}


