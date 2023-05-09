// https://www.sparkfun.com/datasheets/RF/KLP_Walkthrough.pdf

/*
* Simple Transmitter Code
* This code simply counts up to 255
* over and over
* (TX out of Arduino is Digital Pin 1)
*/
byte counter;
void setup(){
//2400 baud for the 434 model
Serial.begin(2400);
counter = 0;
}

void loop(){
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
