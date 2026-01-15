#include "EasyNextionLibrary.h"  // EasyNextionLibrary add functions that simplify the communication and interacting of the arduino and Nextion HMI
//#include "stdio.h"                //C library for add functionality
#define Nexion1 Serial1          //identifies Serial1 channel as a non library managed serial port for direct HMI communication.

EasyNex myNex(Serial1);  // Create an object of EasyNex class with the name < myNex >
                         // Set the Hardware Serial to be used by the EasyNextionLibrary.


/*
Screen communications  happen through Serial1 on Pins 18 and 19.
Those are auto initialized when the Nexion1.begin() is called.
Remember to wire TX(Mega) to RX(screen)  and RX(mega) to TX(screen)
*/


void setup() {
  Serial.begin(9600);    //Start Serial communication of the arduino w/Baud rate 9600
  myNex.begin(9600);     // Begin the Serial communication of the HMI with a baud rate of 9600 for the library
  Nexion1.begin(9600);   //Start the HMI Serial Communication for channel 1
  setupIO();             //Set the pins into their proper mode (INPUT_PULLUP/OUTPUT) [Tab A30]
  initialize();          //Sets all the relays to be in the "off" position [Tab A30]
  redLEDfastFlash(1);    //Calls the function that will flash RED LED on HMI box fast.  Brackets # is how many times [Tab A30]
  redLEDslowFlash(1);    //Calls the function that will flash RED LED on HMI box slow.  Brackets # is how many times [Tab A30]
  greenLEDfastFlash(1);  //Calls the function that will flash GREEN LED on HMI box fast.  Brackets # is how many times [Tab A30]
  greenLEDslowFlash(1);  //Calls the function that will flash GREEN LED on HMI box slow.  Brackets # is how many times [Tab A30]
  greenLEDon();          //Turns the Green LED on the HMI box to be static and on. [Tab A30]
}
