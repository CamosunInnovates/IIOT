//timing events
unsigned long g1currentMillis = 0;    //Current time for the G1 Actuator (round containers dispenser)
unsigned long g1previousMillis = 0;   //previoud time for the G1 Actuator (round containers dispenser)
unsigned long g2currentMillis = 0;    //Current time for the G2 Actuator (square containers dispenser)
unsigned long g2previousMillis = 0;   //Previous time for the G2 Actuator (square containers dispenser)
unsigned long dr1currentMillis = 0;   //Current time for the DR1 Actuator (Material Dispensor Gate)
unsigned long dr1previousMillis = 0;  //previous time for the DR1 Actuator (Material Dispensor Gate)
unsigned long ledcurrentMillis = 0;   //current time for use with LED
unsigned long ledpreviousMillis = 0;  //previous time for use with LED

//Taken From Dispensing_WIP
unsigned long dispensingTimer = 0;     //timer to record how long container has been traveling used to check jams and error states
unsigned long dispensingWait = 15000;  //how long container has to travel to first sensor
unsigned long firstConTimer = 0;       //timer to record how long container has been traveling from sensor 1 to sensor 2
unsigned long firstConWait = 15000;    //how long the container has to travel from sen1 to sen2
unsigned long clearanceTimer;          //time taken for container to pass l2
unsigned long clearanceWait = 2000;    //time A container has to pass l2
unsigned long generalTimer;            //To help with createing a non blocking delay
unsigned long generalWait = 5000;     //A adjustable time to help with non blocking delays


const int ledslowDelay = 500;     //delay in milliseconds for flashing LEDs at a slow speed
const int ledfastDelay = 250;     //delay in milliseconds for flashing LEDs at a fast speed
const int dispcontDelay = 1000;   //delay in milliseconds of how long to keep a container dispensing acutator (G1 & G2) extended/activated
const int gateDelay = 1500;       //delay in milliseconds ???????????
const int applylblDelay = 1000;   //delay in milliseconds to wait until the labeler components finish their actions.
const int containerDelay = 2000;  //delay in milliseconds to helps prevent containers colliding if the next container is dispensed to quickly [Tab A20]
const int irsensDelay = 150;      //delay in milliseconds to slow down the IR sensors from reading to fast and having errors
const int dispbbDelay = 2000;   //delay in milliseconds before the material dispensor gate will open after container has arrrived
const int finishDelay = 13000;  //delay in milliseconds before the conveyors will turn off after an order is complete
const int primeDelay  = 2000;   //delay in milisecond that is used in the priming of the pneumatics 
//BB dispenser piston timing
const int redGateTimer = 900;      //Time in ms for how long the gate will be open when dispensing BBs
const int blueGateTimer = 1100;      //Time in ms for how long the gate will be open when dispensing BBs
const int blueTimeCorrection = 20;  //Time to add to the gate to help it get back to home position
const int redTimeCorrection = 5;  //Time to add to the gate to help it get back to home position


//Item quantities
//used in conjunction with the Nextion HMI to track and dispense orders
int A = 0;    //Item Selection A (Round Container with Blue Material)
int B = 0;    //Item Selection B (Round Container with Red Material)
int C = 0;    //Item Selection C (Square Container with Blue Material)
int D = 0;    //Item Selection D (Square Container with Red Material)
int sum = 0;  //Sum of the total items selected for an order from the HMI (Used for Tracking how many items have been ordered/fullfilled)

int dispensed = 0;  //Used for tracking how many containers have been dispensed
int conSent = 0;  //used for tracking how many containers have been sent to the material dispenser from the container queue
int stmCount = 0; //keeps track of how many times a function has been called, using it for error tracking

//Handles the cases for main program
char casevar = 0;

//informative only - tracks the state of valves
bool g2Active = false;    //G1-Acturator/Square container set to being in the de-activated position
bool g1Active = false;    //G2-Actuator/Round container set to being in the de-activated position
bool dr1bActive = false;  //DR1-Gate Acutator set to being in the de-active postion

//Names should be changed as theses are confusing and not reflecting what they are controlling.
//All other vairable names are fairly self explanitory
bool irSensor1 = false;                                               //IR sensor1 True when container detected, false when no container detected.  First Sensor after Container Dispensor
bool irSensor2 = false;                                              //IR sensor2 True when container detected, false when no container detected    Sensor for queue to material dispenser
bool irSensor3 = false;                                              //IR sensor3 True when container detected, false when no container detected    Sensor at the material dispenser to confirm containers are their 
bool irSensor4 = false;                                              //IR sensor4 True when container detected, false when no container detected
bool irSensor5 = false;                                              //IR sensor5 True when container detected, false when no container detected    Sensor at the labeler to confirm that containers are there
bool irSensor6 = false;                                              //IR sensor6 True when container detected, false when no container detected
bool irstatearray[] = { irSensor1, irSensor2, irSensor3, irSensor4, irSensor5, irSensor6 };  //Array containing the line IR sensors values.

//for functions that need to keep track of the previous sensor dection state
bool lastStateIR1;
bool lastStateIR2;
bool lastStateIR3;
bool lastStateIR4;
bool lastStateIR5;
bool lastStateIR6;

bool filledState = false;  //used to determine if the container sent to the material dispenser has been filled


//State Varibles from Dispensing_WIP
bool firstConState = false;   //tracks  if the first container got dispenced
bool dispConState = false;    //determines if a container has been dispenced and is traveling
bool l2State = false;         // is actuator L2 open or closed
bool nextCon = false;         //determines if another container can be dispenced
bool clearanceState = false;  //activate clearance timer for the container to clear L2


/*
----------------IR SENSORS SECTION----------------
For documentation, refer to IRsens-IIOT.ino by Luke R

*/
//IR Sensor Variables for operation that Are passed to IR Matrix
//See discriptions for Sensor 1 for variable function as these apply to all of ther IR sensors
//IR Sensor 1
float volts1;           //used to calculate the distance the IR is reading
float distance1;        //Distance the IR is reading
int detectValue1 = 11;  //Sensor reading Value that the detect is measured against to trigger logic

//See discriptions above for variable function
//IR Sensor 2
float volts2;
float distance2;
int detectValue2 = 16;

//IR Sensor 3
float volts3;
float distance3;
float detectValue3 = 6.5;

//IR Sensor 4
float volts4;
float distance4;
int detectValue4 = 16;

//IR Sensor 5
float volts5;
float distance5;
int detectValue5 = 16;

//IR Sensor 6
float volts6;
float distance6;
int detectValue6 = 16;

int cal = 2;  //Calibration factor for finding distances

//Matrix[y][x] size to help with logic (Make sure it matches irSensorM)
int y = 6;  //rows of matrix
int x = 3;  //columns of matrix

//Matrix containing all the values that the IR sensors need to operate collect (Make sure it matches variables y & x)
float irSensorM[6][3] = {
  { volts1, distance1, detectValue1 },
  { volts2, distance2, detectValue2 },
  { volts3, distance3, detectValue3 },
  { volts4, distance4, detectValue4 },
  { volts5, distance5, detectValue5 },
  { volts6, distance6, detectValue6 }
};