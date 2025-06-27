//Define output bits (b0 = bit 0)
#define b0 2


bool bit_waiting = 0;
bool bit = 0;
bool transmitting = 0;
bool bit_before = 0;
bool bit_now = 0;
bool test = 0;


int beginning_interrupt_number = 0;
uint16_t clock_time_first = 0;
uint16_t clock_time_second = 0;

ISR(INT0_vect){
  //if not transmitting, then we need to detect for that initial 0 and learn the speed
  if (!transmitting){
    if (beginning_interrupt_number == 0){            //is this the first interrupt:
      //Serial.println("first");
      TCCR1B = 0b00000100;                           //Prescaler of clk/256. CHANGE THIS LATER
      TCCR1A = 0b00000000;
      TCNT1 = 0x0000;                                //Set timer value to 0
      TIFR1 |= (1<<TOV1);                            //clear the timer overflow interrupt flag in case it was triggered
      TIMSK1 |= (1<<TOIE1);                          //Turn on timer overflow interrupt. In case we get stuck here
      beginning_interrupt_number = 1;
      EICRA &= ~(1<<ISC00);                           //Change interrupt to falling edge
    }
    else if (beginning_interrupt_number == 1){       //else if this is the second interrupt:
      //Serial.println("second");
      clock_time_first = TCNT1;                      //get time since last interrupt
      //Serial.println(clock_time_first);
      TCNT1 = 0x0000;
      beginning_interrupt_number = 2;
      EICRA |= (1<<ISC00);                           //Change external interrupt back to rising edge
    }
    else if (beginning_interrupt_number == 2){       //else if this is the third interrupt:
      clock_time_second = TCNT1;                     //get time since last interrupt
      //Serial.println(clock_time_second);
      if ((clock_time_first - clock_time_second <= 50) && (clock_time_first - clock_time_second >= 0) || (clock_time_second - clock_time_first <= 50) && (clock_time_second - clock_time_first >= 0)){  //are the times close?
        transmitting = 1;                            //We are now considered transmitting
        //Serial.println("receive");
        bit_before = digitalRead(b0);                //Keep track of input bit now, we need to know if it changes
        OCR1A = clock_time_second * 1.5;             //set timer1 compare match A to be timer1 value * 1.5
        EIMSK &= ~(1<<INT0);                         //Turn off external interrupt
        EICRA &= ~(1<<ISC01);                        //Set external interrupt to rising and falling (for later)
        EICRA |= (1<<ISC00);
        TCNT1 = 0x0000;                              //Reset timer to 0
        TCCR1A |= (1<<COM1A1) | (1<<COM1A0);         //Set OC1A on compare match
        TIFR1 |= (1<<OCF1A);
        TIMSK1 |= (1<<OCIE1A);                       //turn on timer compare interrupt
        beginning_interrupt_number = 0;
      }
      else{
        beginning_interrupt_number = 0;              //not close. This is not a real data start
      }
    }
  }


  //if transmitting
  else{
    EIMSK &= ~(1<<INT0);                             //Turn off external interrupt
    TCNT1 = 0x0000;                                  //Reset timer1 value
    TIMSK1 |= (1<<OCIE1A);                           //Turn on timer1 interrupt
    bit_before = digitalRead(b0);                    //Keep track of input bit now, we need to know if it changes
    //Serial.println("ext");
  }
}

//If timer overflows, assume a communication error occurred
ISR(TIMER1_OVF_vect){
  TIMSK1 &= ~(1<<TOIE1);                             //Turn off overflow interrupt
  TCNT1 = 0x0000;                                    //Reset timer back to 0
  transmitting = 0;
  bit = 0;
  bit_before = 0;
  beginning_interrupt_number = 0;
  //Serial.println("done");
}

ISR(TIMER1_COMPA_vect){
  bit_now = digitalRead(b0);                         //Read input bit now
  if (bit_before == bit_now){                               //Did it change or stay the same?
    bit = 1;                                         //If same, this is a 1
  }
  else{
    bit = 0;                                         //If different, this is a 0
  }
  TIMSK1 &= ~(1<<OCIE1A);                            //Turn off timer1 interrupt
  EIFR |= (1<<INTF0);
  EIMSK |= (1<<INT0);                                //Turn on external interrupt
  bit_waiting = 1;                                   //Tell main loop there is a bit waiting
  //Serial.println(bit);
}

void setup() {
  Serial.begin(9600);
  EICRA |= (1<<ISC01) | (1<<ISC00);                             //Interrupt on rising edge of pin 2 (INT0)
  EIMSK |= (1<<INT0);                              //Turn on external interrupt
}

void loop() {
  int thisbyte = 0;
  if (transmitting){
    for (int i=7; i>=0; i--){
      while (!bit_waiting && transmitting){
        _delay_us(1);
      }
      thisbyte |= bit << i;
      bit_waiting = 0;
    }
    if (transmitting){                            //fix random 128 showing at end
      Serial.write(thisbyte);
    }
  }
  
}