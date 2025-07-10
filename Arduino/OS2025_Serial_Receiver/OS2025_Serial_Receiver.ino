#include <SoftwareSerial.h>
SoftwareSerial receiver(10,11); // RX | TX

#define STATUS_LED 3

int time = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(STATUS_LED, OUTPUT);
  Serial.begin(57600);
  receiver.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (receiver.available() > 0){
    Serial.write(receiver.read());
    time = 0;
    digitalWrite(STATUS_LED, 1);
  }
  else{
    time++;
    if (time > 10000){
      digitalWrite(STATUS_LED, 0);
      time = 10000;
    }
  }
  delay(0.1);
}
