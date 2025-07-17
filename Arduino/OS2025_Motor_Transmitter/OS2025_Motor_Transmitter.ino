
#include <Stepper.h>

// Define pin connections
const int dirPin = 5;
const int stepPin = 2;
const int enablePin = 8;

#define INIT_FREQUENCY 1


int FREQUENCY = INIT_FREQUENCY;
bool transmitting_now = 0;
bool buffer_big_enough = 0;

Stepper Stepper(200, stepPin, dirPin);

bool bit;
int bitcount;
int lastBit = -1;
bool firstCall = true;

void bitTransmitter() {
  static int lastBit = 0;

  int steps;

  if (firstCall) {
    steps = 640;
    firstCall = false;
  } else if (bit == lastBit) {
    steps = 640;
  } else {
    steps = 1000;
  }

  if (bit == 1) {
    Stepper.step(steps);
  } else {
    Stepper.step(-steps);
  }

  //delay(5);
  bitcount++;
  lastBit = bit;
}
// Creates an instance


void setup() {

  Serial.begin(9600);

Stepper.setSpeed(100000); //change this to change the speed

  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);

}

void loop() {
  
  if (Serial.available() > 0){             //If bytes are waiting at the serial port, we must be transmitting
    if (transmitting_now == 0){

      //IF THE MOTOR NEEDS ANY INITIALIZATION BEFORE TURNING, DO IT HERE

    }

    transmitting_now = 1;
    
    
    int thisbyte = Serial.read();          //Read one byte from serial port
    for (int i=7; i>=0; i--){              //Loop 8 times (8 bits per byte)
      bit = (thisbyte >> i) & 1;           //Pull out this bit ("shift" the bits right until it is in the least significant place)

      bitTransmitter();
      delay(1);
      //delay(1000/FREQUENCY);               //Loop delay
    }
    
    if (Serial.available() > 16){          //Some weird bug was happening where the serial port was filling up too slowly, the first 16 bytes triggered a 1 to send. I think this will fix it
      buffer_big_enough = 1;
    }
    if (Serial.available() == 16 && buffer_big_enough == 1){          //If there are 8 bytes left in the serial port, send a 1 to the connected program
      Serial.write("1");
    }
  }
  
  else{                                    //Turn everything off if we're not transmitting anything
    transmitting_now = 0;
    buffer_big_enough = 0;
    //PUT YOUR MOTOR INTO A SAFE STATE HERE. TURN STUFF OFF IF NEEDED, ETC.
    firstCall = true;
  }
}
