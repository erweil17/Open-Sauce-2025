//Differential manchester transmitter
//An extra zero bit is inserted at the beginning of every message for clock sync
//Only 64 chars fit in the serial buffer. A 1 is transmitted when 8 are left

//Define output bits (b0 = bit 0)
#define b0 2
#define STATUS_LED 3
#define BIT_LED 4


//Set this to number of bits per second. Touch max is 5000, light max is 1000
#define INIT_FREQUENCY 5000

bool bit = 0;
bool b0_state = 0;
bool bit_transmitted = 1;
bool data_ready = 0;
bool clock = 1;
bool transmitting_now = 0;
int FREQUENCY = INIT_FREQUENCY;


//Interrupt. Runs FREQUENCY*2 times per second
ISR(TIMER1_COMPA_vect){
  if (data_ready){
    if (clock){    //this is the clock. It always changes
      //Serial.print("c");
      b0_state = !b0_state;
    }
    else{
      if (bit == 0){   //if a 0, change the state
        //Serial.print("0");
        b0_state = !b0_state;
      }
      else{            //if a 1, don't
        //Serial.print("1");
      }
      bit_transmitted = 1;
    }
    digitalWrite(b0, b0_state);  //add ! to make active low
    clock = !clock;
  }
  else{                //write everything to a 0 if not transmitting
    b0_state = 0;
    digitalWrite(b0, 0);   //change to 1 to make active low
    clock = 1;
  }
}



void setup() {
  //Set pins to output mode
  pinMode(b0, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(BIT_LED, OUTPUT);
  Serial.begin(9600);

  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 62500/FREQUENCY/2;  // compare match register 16MHz/256/FREQUENCY
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}



void loop() {
  
  if (Serial.available() > 0){
    digitalWrite(STATUS_LED, 1);
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
        OCR1A = 62500/FREQUENCY/2;  // compare match register 16MHz/256/FREQUENCY
        Serial.println("OK");
      }
      int temp = 0;                  //Now flush the buffer so we dont transmit this command
      while (Serial.available() && temp < 10){
        Serial.read();
        temp++;
      }
      temp = 0;
    }
    else{                            //else this is not a command
      if (!transmitting_now){        //Did we just start transmitting a message?
        bit_transmitted = 0;         //If so, send a zero so the receiver can sync
        bit = 0;
        data_ready = 1;              //Tell interrupt we are ready
        while (!bit_transmitted){    //Wait until interrupt has executed
          _delay_us(1);
        }
      }

      transmitting_now = 1;          //Now transmit actual message
    
      for (int i=7; i>=0; i--){      //Transmit next 7 bits
        bit_transmitted = 0;
        bit = (thisbyte >> i) & 1;
        digitalWrite(BIT_LED, bit);
        data_ready = 1;              //Tell interrupt we are ready
        while (!bit_transmitted){    //Wait until interrupt has executed
          _delay_us(1);
        }
      }
    }

    
  }

  else{                            //No data in serial port
    data_ready = 0;
    transmitting_now = 0;
    digitalWrite(BIT_LED, 0);
    digitalWrite(STATUS_LED, 0);
  }
  if (Serial.available() == 16){    //Send a 1 if serial buffer nearly empty
      Serial.write("1");
  }
}