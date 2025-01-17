//--------------------------------------
//      DECLARING STUFF
//--------------------------------------

// Testing variables
volatile bool isr_flag = false;
int count = 0;
int test_pin = 7;

// Flow Sensor Variables
int num_sensors = 5;
volatile int flow_pin[5] = {2,3,4,5,6};
volatile int flow_pin_new_state[5] = {0,0,0,0,0};
volatile int flow_pin_old_state[5] = {0,0,0,0,0};
volatile int flow_pulse_count[5] = {0,0,0,0,0};

//======================================
//      SETUP FUNCTION
//======================================
void setup()
{
  cli(); //disable interrupts
  
  // test pin setup
  pinMode(test_pin,OUTPUT);
  digitalWrite(test_pin,LOW);
  
  // initialize Timer1
  TCCR1A = 0;    // set entire TCCR1A register to 0
  TCCR1B = 0;    // set entire TCCR1B register to 0 
                 // (as we do not know the initial  values) 
  
  // enable Timer1 overflow interrupt:
  TIMSK1 |= (1 << TOIE1);
  // Preload with value 3036
  //use 64886 for 100Hz
  //use 64286 for 50 Hz
  //use 34286 for 2 Hz
  TCNT1=0x0BDC;
  // Set CS10 bit so timer runs at clock speed: (no prescaling)
  TCCR1B |= (1 << CS12); // Sets bit CS12 in TCCR1B
    
  Serial.begin(9600);
  Serial.print(0);
  sei();
}

//======================================
//      TIMER INTERRUPT
//======================================
//This is the timer overflow interrupt
//This is where we will determine the input pulse states
//and keep a count of the number of pulses
ISR(TIMER1_OVF_vect)
{
  isr_flag = true;
  TCNT1=0x0BDC; // reload the timer preload
}


//======================================
//      MAIN LOOP
//======================================
void loop()
{
  //------this happens when the timer overflows
  if (isr_flag == true)
  {
    count++;
    if (count >= 10)
    {
      count = 0;
    }
    Serial.print(count);
    
    isr_flag = false;
  }
  
  //-------this happens all the time as fast as possible
  // poll each sensor input
  for (int p=0;p<num_sensors;p++)
  {
    // read the input value
    flow_pin_new_state[p] = digitalRead(flow_pin[p]);
    //is it different? Looking for a rising edge
    if ((flow_pin_new_state[p] == HIGH) && (flow_pin_old_state[p] == LOW))
    {
      flow_pulse_count[p]++;
    }
    flow_pin_old_state[p] = flow_pin_new_state[p];
  }
}
