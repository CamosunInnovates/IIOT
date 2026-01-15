//pin locations
//IR SENSORS
/*
const int irSredhophi = A4;
const int irSredhopmid = A5;
const int irSredhoplow = A6;
const int irSbluhophi = A7;
const int irSbluhopmed = A8;
const int irSbluhoplow = A9;
*/

//IR sensor is Sharp GP2Y0A51SK0F
//Refer to A31_IRsensFunctions.ino
const int irScontDisp = A11;    //Detects if Containers have been dispenced
const int irScontready = A10;   //Detects if a container is in line and waiting to be sent to Material Dispensor
const int irSbbfilltgt = A12;   //Detects if container is at the material dispenser
const int irSlblqueuef1 = A13;  //Detects if there is a container in the labeler queue
const int irSlabeltgtf2 = A14;  //Detects if there is a container in the lableler target
const int peelLabel = A15;    //used for switching the labeler relay to advance labels


//Material Dispencing REED SWITCHES
//The Switch to determine of the material Gate is in the proper position
const int reedSw1 = 29;
const int reedSw2 = 30;  //not currently installed in machine

//CONTAINER DISPENSER
const int contdispSqg2 = 42;   //Actuator G2, Dispenses the Square container
const int contdispCirg1 = 41;  //Actuator G1 dispenses the Round containers
const int contLockl1 = 32;     //First line actuator L1.  It has a bellowed feature on the end to clamp containers to hold them in position

//BB DISPENSER
//Jesus to comment
const int actuatorL2 = 33;   //Actuator L2, Gate that allows flow of empty containers from the "empty ready buffer".
const int actuatorL3 = 34;  //Actuator L3, Gate that stops an empty container under dispensing target location.
const int actuatorL4 = 35;  //Actuator L4, gate that stops the full containers before the labeler in the "full ready buffer".
const int bbdispReddr1a = 38;    //Actuator DR1 side A, opperates the bb dispanser gate. Theoretically allows red bbs to flow.
const int bbdispBludr1b = 39;    //Actuator DR1 side B, opperates the bb dispanser gate. Theoretically allows blue bbs to flow.

//LABELER
//Jesus to comment
const int actuatorL5 = 36;    //Actuator L5, Gate that stops the full container in the labeling location.
const int rotorR1 = 31;     //Actuator R1, rotates the piston from label pickup location to label application location.
const int actuatorG3 = 43;    //Actuator G3, extends or retracts the label applicator(suction cup) piston.
const int vacuumV1 = 40;  //Actuator V1, enables or disables the Vacum for the applicator (suction cup).
const int actuatorL6 = 37;

//CONVEYORS
//Currently three conveyors all on one circuit.  They may be split up in the future.
const int conveyors = 47;

//LEDS
const int redLED = 46;    //Red LED on the HMI control box
const int greenLED = 45;  //Green LED on the HMI control box

//SPARES
