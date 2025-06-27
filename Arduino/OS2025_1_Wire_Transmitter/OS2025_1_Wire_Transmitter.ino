//Differential manchester transmitter
//An extra zero bit is inserted at the beginning of every message for clock sync
//Only 64 chars fit in the serial buffer. A 1 is transmitted when 8 are left

//Define output bits (b0 = bit 0)
#define b0 2

//Set this to number of bits per second. Touch max is 2000, light max is 1000
#define FREQUENCY 500

bool bit = 0;
bool b0_state = 0;
bool bit_transmitted = 1;
bool data_ready = 0;
bool clock = 1;
bool transmitting_now = 0;


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
    digitalWrite(b0, b0_state);
    clock = !clock;
  }
  else{                //write everything to a 0 if not transmitting
    b0_state = 0;
    digitalWrite(b0, 0);
    clock = 1;
  }
}



void setup() {
  //Set pins to output mode
  pinMode(b0, OUTPUT);
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
    if (!transmitting_now){        //Did we just start transmitting a message?
      bit_transmitted = 0;         //If so, send a zero so the receiver can sync
      bit = 0;
      data_ready = 1;              //Tell interrupt we are ready
      while (!bit_transmitted){    //Wait until interrupt has executed
        _delay_us(1);
      }
    }

    transmitting_now = 1;          //Now transmit actual message
    int thisbyte = Serial.read();
    for (int i=7; i>=0; i--){      //Transmit next 7 bits
      bit_transmitted = 0;
      bit = (thisbyte >> i) & 1;
      data_ready = 1;              //Tell interrupt we are ready
      while (!bit_transmitted){    //Wait until interrupt has executed
        _delay_us(1);
      }
    }
  }

  else{                            //No data in serial port
    data_ready = 0;
    transmitting_now = 0;
  }
  if (Serial.available() == 8){    //Send a 1 if serial buffer nearly empty
      Serial.write("1");
  }
}