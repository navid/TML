/*
   Topological Media Lab
   Thierry Dumont
   2018-02
   Atmosphere Residency

   Monitor Serial
   Change state of pin
   Serial 5

   Right if front facing
*/

#include <Atomizer.h>

const int numAtomizers = 18; //Variable for number of atomizers

//Array of atomizers
Atomizer atomizers[numAtomizers];

//Array of pins for atomizers
int atomizerPins[numAtomizers] = {
  17,
  16,
  14,
  38,
  37,
  36,
  35,
  30,
  29,
  10,
  9,
  8,
  7,
  6,
  5,
  4,
  3,
  2
};

int startTag = 44;//Start value meassge
int endTag = 22;//End value message

int serialVal1 = -1;//Start Tag
int serialVal2 = -1;//Atomizer ID
int serialVal3 = -1;//Atomizer new state
int serialVal4 = -1;//Closing tag



void setup()
{

  //Serial.begin(9600);//Computer
  Serial1.begin(9600);//Leader Input

  //Dynamically set pins for atomizers
  for (int i = 0; i < numAtomizers; i++) {
    atomizers[i].set_Pin(atomizerPins[i]);  // attaches the servo on pin 9 to the servo object
  }

}

void loop()
{
  //----------------------------
  //Receive new states
  if (Serial1.available() > 0) {    // if there is serial data in the queue

    serialVal1 = Serial1.read();
    serialVal2 = Serial1.read();
    serialVal3 = Serial1.read();
    serialVal4 = Serial1.read();

    if (serialVal1 == startTag && serialVal4 == endTag  && (serialVal3 >= 0 || serialVal3 <= 255)) {
      serialVal2 = serialVal2 - 19; //Because taking care of Atomizer 19 to
      atomizers[serialVal2].on(serialVal3);//stay one second on, then a second off
    } else {
      Serial1.clear();
    }
  }
  delay(10);
}//End for loop


