
#include <Arduino.h>
#include <RotaryEncoder.h>


#define PIN_IN1 2
#define PIN_IN2 3

uint8_t fifoByte = 0;
uint8_t bitCount = 0;
bool halfturn_right = 0;
bool halfturn_left = 0;
int time_counter = 0;

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

void setup()
{
  Serial.begin(9600);
} 


// Read the current position of the encoder and saves it as a bit into a one bite array. first in first out. once the byte is full (8 position changes),
// prints out the value in base ten. Then resets.
void loop()
{
  static int pos = 0;
  
  encoder.tick();

  int newPos = encoder.getPosition();
  int bit = (int)(encoder.getDirection());

  
  if (pos != newPos) {
    time_counter = 0;
    pos = newPos;
    
    //if turned right
    if (bit == 1){
      //if we already turned half way
      if (halfturn_right == 1){
        shiftInBit(1);
        halfturn_left = 0;
        halfturn_right = 0;
      }
      //this is only half way
      else{
        halfturn_right = 1;
        halfturn_left = 0;
      }
    }

    //if turned left
    if (bit == -1){
      if (halfturn_left == 1){
        shiftInBit(0);
        halfturn_right = 0;
        halfturn_left = 0;
      }
      else{
        halfturn_left = 1;
        halfturn_right = 0;
      }
    }
  } 
  else{
    delay(1);
    time_counter += 1;
    //its been 3 seconds since the encoder turned, assume cancelled
    if (time_counter == 3000){
      bitCount = 0;
      fifoByte = 0; // Reset if needed
      //halfturn_right = 0;
      //halfturn_left = 0;
    }
  }
} 

void shiftInBit(uint8_t bit) {
  bit = bit & 0x01;                 // Ensure it's 0 or 1
  fifoByte = (fifoByte << 1) | bit; // Shift left and add bit
  bitCount++;
  if (bitCount == 8) {
    Serial.write(char(fifoByte));
    bitCount = 0;
    fifoByte = 0; // Reset if needed
  }
}
