// reading liquid flow rate using Seeeduino and Water Flow Sensor from Seeedstudio.com
// Code adapted by Charles Gantt from PC Fan RPM code written by Crenn @thebestcasescenario.com
// http:/themakersworkbench.com http://thebestcasescenario.com http://seeedstudio.com

volatile int NbTopsFan; //measuring the rising edges of the signal
int Calc;                              
int hallsensor = 2;    //The pin location of the sensor
int DevNum = 0;        //device number (unique number for each flow sensor)

void rpm ()     //This is the function that the interupt calls
{
 NbTopsFan++;  //This function measures the rising and falling edge of the hall effect sensors signal
}
// The setup() method runs once, when the sketch starts
void setup() //
{
 pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
 Serial.begin(9600); //This is the setup function where the serial port is initialised,
 attachInterrupt(0, rpm, RISING); //and the interrupt is attached
}
// the loop() method runs over and over again ,
// as long as the Arduino has power
void loop ()    
{
 NbTopsFan = 0;      //Set NbTops to 0 ready for calculations
 sei();            //Enables interrupts
 delay (100);       //Wait 10ms
 cli();            //Disable interrupts
 Calc = (NbTopsFan * 60 / 7.5); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/hour
 Serial.print (DevNum, DEC); //Prints Device Number (unique number for each flow sensor)
 Serial.print (" "); //Print space to seperate Device Number and calculated flow speed.
 Serial.print (Calc, DEC); //Prints the number calculated above (in L/hour)
 Serial.print ("\r\n"); //Prints "L/hour" and returns a  new line
}

