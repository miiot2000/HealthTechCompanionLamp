# Write your code here :-)
#Red LED Light Testing
# SPDX-FileCopyrightText: 2021 ladyada for Adafruit Industries
# SPDX-License-Identifier: MIT
import time;
import board;
from adafruit_circuitplayground import cp;

# """This example turns on the little red LED."""

# Use this code to initially test if the NeoPixel Ring is working and blinking at the right time
# while True:
#     cp.red_led = not cp.red_led;
#     time.sleep(1.0);

"""This example uses the capacitive touch pads on the Circuit Playground. They are located around
the outer edge of the board and are labeled A1-A6 and TX. (A0 is not a touch pad.) This example
lights up all the NeoPixels a different color of the rainbow for each pad touched!"""

#This sample code is assuming the capacitive sensors are already attached to the NeoPixel Rings
#For this sample will only have up to A5 as we only have a max of 5 touch sensors
#I'm trying to see if I can write code with the assumption that the touch sensors and neopixel ring are two seperate things

cp.pixels.brightness = 0.5;

while True:
    if cp.touch_A1:
        print("Sensor 1 has been touched");
        cp.pixels.fill((255, 0, 0));

    if cp.touch_A2:
        print("Sensor 2 has been touched");
        cp.pixels.fill((215, 0, 0));

    if cp.touch_A3:
        print("Sensor 3 has been touched!");
        cp.pixels.fill((155, 100, 0));
    if cp.touch_A4:
        print("Sensor 4 has been touched!");
        cp.pixels.fill((0, 255, 0));
    if cp.touch_A5:
        print("Sensor 5 has been touched!")
        cp.pixels.fill((0, 135, 125));








