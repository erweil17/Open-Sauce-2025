//This program accepts up to 64 bytes at a time and sends them over 9 IO ports to another Arduino
//The 64 bytes is an Arduino limitation. If more are sent the last ones will be discarded
//This program returns a "1" over the serial port when it has only 8 bytes remaining in its serial queue, meaning when the "1" is received it is safe to send up to 56 more bytes

//Define output bits (b0 = bit 0)
#define b0 2


//Set this to number of bytes per second
#define INIT_FREQUENCY 1

bool bit = 0;
int FREQUENCY = INIT_FREQUENCY;

void setup() {
  //Set pins to output mode
  pinMode(b0, OUTPUT);
  Serial.begin(9600);
}



void loop() {
  //If bytes are waiting at the serial port, read the oldest one and move its binary value into output bits 0-7
  if (Serial.available() > 0){
    int thisbyte = Serial.read();
    for (int i=7; i>=0; i--){      //Transmit next 7 bits
      bit = (thisbyte >> i) & 1;
      Serial.println(bit);
      delay(1000/FREQUENCY);
    }
    //If there are 8 bytes left in the serial port, send a 1 to the connected program
    if (Serial.available() == 8){
      Serial.write("1");
    }
  }
  //Turn everything off if we're not transmitting anything
  else{
    digitalWrite(b0, 1);
  }
}