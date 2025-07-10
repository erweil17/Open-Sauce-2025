#include <SoftwareSerial.h>
SoftwareSerial transmitter(11,10); // RX | TX

#define STATUS_LED 3

int time = 0;
bool out_of_bits = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(STATUS_LED, OUTPUT);
  Serial.begin(57600);
  transmitter.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available() > 0){
    out_of_bits = 0;
    transmitter.write(Serial.read());
    time = 0;
    digitalWrite(STATUS_LED, 1);
  }
  else{
    if (out_of_bits == 0){
      Serial.write("1");
      out_of_bits = 1;
    }
    time++;
    if (time > 10000){
      digitalWrite(STATUS_LED, 0);
      time = 10000;
    }
  }
  delay(0.1);
}
