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

bool previous_press = false;

//Receives data from 8 inputs and OR's them into thisbyte
void receive(){
  uint8_t thisbyte = 0;
  thisbyte |= (digitalRead(b0) << 0);
  thisbyte |= (digitalRead(b1) << 1);
  thisbyte |= (digitalRead(b2) << 2);
  thisbyte |= (digitalRead(b3) << 3);
  thisbyte |= (digitalRead(b4) << 4);
  thisbyte |= (digitalRead(b5) << 5);
  thisbyte |= (digitalRead(b6) << 6);
  thisbyte |= (digitalRead(b7) << 7);
  //Send the received byte over the serial port
  char thischar = char(thisbyte);
  Serial.write(thischar);
}

int debounce_press(){
  static uint16_t pressed_state = 0x0000;
  pressed_state = (pressed_state << 1) | (!digitalRead(2)) | 0xE000;
  if (pressed_state == 0xF000) return 1;
  return 0;
}

int debounce_depress(){
  static uint16_t depressed_state = 0x0000;
  depressed_state = (depressed_state << 1) | (digitalRead(2)) | 0xE000;
  if (depressed_state == 0xF000) return 1;
  return 0;
}

void setup() {
  //Set pins to input mode
  pinMode(b0, INPUT);  //we will likely want this as INPUT_PULLUP in the final design, or use external pullups
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);
  pinMode(b7, INPUT);
  pinMode(clock, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (debounce_press() and digitalRead(2) == 1 and previous_press == false){
    receive();
    previous_press = true;
  }
  delay(0.1);
  if (debounce_depress() and digitalRead(2) == 0 and previous_press == true){
    receive();
    previous_press = false;
  }
  delay(0.1);
}