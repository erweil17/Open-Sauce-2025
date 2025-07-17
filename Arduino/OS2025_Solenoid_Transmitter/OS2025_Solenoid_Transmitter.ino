//This program accepts up to 64 bytes at a time and sends them over 9 IO ports to another Arduino
//The 64 bytes is an Arduino limitation. If more are sent the last ones will be discarded
//This program returns a "1" over the serial port when it has only 8 bytes remaining in its serial queue, meaning when the "1" is received it is safe to send up to 56 more bytes

//Define output bits (b0 = bit 0)
#define b0 3
#define b1 4
#define b2 5
#define b3 6
#define b4 7
#define b5 8
#define b6 9
#define b7 10
#define clock 2

//Set this to number of bytes per second
#define INIT_FREQUENCY 8

int FREQUENCY = INIT_FREQUENCY;
bool clock_state = 0;
bool transmitting_now = 0;

void setup() {
  //Set pins to output mode
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  pinMode(b6, OUTPUT);
  pinMode(b7, OUTPUT);
  pinMode(clock, OUTPUT);
  Serial.begin(9600);
  digitalWrite(clock, 0);
}



void loop() {
  //If bytes are waiting at the serial port, read the oldest one and move its binary value into output bits 0-7
  if (Serial.available() > 0){
    int thisbyte = Serial.read();

    if (thisbyte == 63 && transmitting_now == 0){    //if this is a command. Commands start with ?
      delay(10);
      int command = Serial.read();
      int argument = (Serial.read() - 48);
      argument = (argument * 10) + (Serial.read() - 48);
      argument = (argument * 10) + (Serial.read() - 48);
      argument = (argument * 10) + (Serial.read() - 48);
      if (command == 70){            //F command for changing frequency
        FREQUENCY = argument;
        Serial.println("OK");
      }
      int temp = 0;                  //Now flush the buffer so we dont transmit this command
      while (Serial.available() && temp < 10){
        Serial.read();
        temp++;
      }
      temp = 0;
    }

    else{
      transmitting_now = 1;
      digitalWrite(b7, (thisbyte & 0b10000000));
      digitalWrite(b6, (thisbyte & 0b01000000));
      digitalWrite(b5, (thisbyte & 0b00100000));
      digitalWrite(b4, (thisbyte & 0b00010000));
      digitalWrite(b3, (thisbyte & 0b00001000));
      digitalWrite(b2, (thisbyte & 0b00000100));
      digitalWrite(b1, (thisbyte & 0b00000010));
      digitalWrite(b0, (thisbyte & 0b00000001));
      //Wait for 1/2 period for bits to settle
      delay((1000/FREQUENCY)*0.5);
      //Toggle the clock
      clock_state = !clock_state;
      digitalWrite(clock, clock_state);
      //If there are 16 bytes left in the serial port, send a 1 to the connected program
      if (Serial.available() == 16){
        Serial.write("1");
      }
    }

  }
  //Turn everything off if we're not transmitting anything
  else{
    transmitting_now = 0;
    digitalWrite(b7, 0);
    digitalWrite(b6, 0);
    digitalWrite(b5, 0);
    digitalWrite(b4, 0);
    digitalWrite(b3, 0);
    digitalWrite(b2, 0);
    digitalWrite(b1, 0);
    digitalWrite(b0, 0);
    delay((1000/FREQUENCY)*0.5);
    clock_state = 0;
    digitalWrite(clock, clock_state);
  }
  //Wait for 1/2 period before sending again
  delay((1000/FREQUENCY)*0.5);
}