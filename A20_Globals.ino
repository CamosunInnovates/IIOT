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
unsigned long generalWait = 5000;      //A adjustable time to help with non blocking delays
unsigned long conveyorTimer;           //To help with non blocking and turning conveyor off after order is complete
unsigned long conveyorWait = 15000;    //An adjustible timer to assist with shutting off the convyer


const int ledslowDelay = 500;     //delay in milliseconds for flashing LEDs at a slow speed
const int ledfastDelay = 250;     //delay in milliseconds for flashing LEDs at a fast speed
const int dispcontDelay = 1000;   //delay in milliseconds of how long to keep a container dispensing acutator (G1 & G2) extended/activated
const int gateDelay = 1500;       //delay in milliseconds ???????????
const int applylblDelay = 1000;   //delay in milliseconds to wait until the labeler components finish their actions.
const int containerDelay = 2000;  //delay in milliseconds to helps prevent containers colliding if the next container is dispensed to quickly [Tab A20]
const int irsensDelay = 150;      //delay in milliseconds to slow down the IR sensors from reading to fast and having errors
const int dispbbDelay = 2000;     //delay in milliseconds before the material dispensor gate will open after container has arrrived
const int finishDelay = 13000;    //delay in milliseconds before the conveyors will turn off after an order is complete
const int primeDelay = 2000;      //delay in milisecond that is used in the priming of the pneumatics


//BB dispenser piston timing
const int redGateTimer = 100;       //Time in ms for how long the gate will be open when dispensing BBs
const int blueGateTimer = 100;     //Time in ms for how long the gate will be open when dispensing BBs
const int blueTimeCorrection = 20;  //Time to add to the gate to help it get back to home position
const int redTimeCorrection = 5;    //Time to add to the gate to help it get back to home position


//Timings for Labeler
unsigned long labelApplicationStart;        //Varible for keeping time during the labeler process
unsigned long dispenseLabelTimer = 750;     //Used for timing to dispence and peel a label
unsigned long v1Timer;    //varible fo keeping time for the v1 to be active
unsigned long g3Timer;    //varible to keep time for the g3 being a
unsigned long r1Timer;    //Variable to keep time for the rotation of Actuator R1
unsigned long v1Delay = 1500;   //Delay for v1 to allow vacuum to start
unsigned long g3Delay = 1200;   //delay to allow actuator G3 to extend/retract
unsigned long r1Delay = 1500;   //Delay for the rotation of R1
unsigned long wakeDymo = 30000;  //the Dymo labeler needs to be woken before dispensing a label its wake window is for 30seconds after last activation
unsigned long lastDispensed = millis();    //used for tracking if the printer needs to be woken
unsigned long clearL4 = 3000;  //Time it takes to get from L3 to  past L4 gate


//Labeler states
bool v1Ready = false;   //State for V1 
bool g3Ready = false;   //States for G3
bool r1Ready = false;   //States of R1
bool labelReady = false;    //State ti declare the printer is ready to print a label
bool containerOne = false;    //State to determine if the first container is being sent from Material Dispenser to LAbel
bool holdL4 = false;        //State to determine if a container needs to be held at actuator L4
bool L4Closed = false;      //Sets state to give feed back if the actuator for L4 is open or closed

//Tracking Varaibles  for Labeller
int sendToLabeler = 0;      //Used for counting how many containers have been sent to the labeler from the Material Dispenser
int labelApplied = 0;       //used for counting how many containers have had a label applied to it
int labelcaseVar = 0;       //Variable used to jump between cases for label handeling [Tab A33]




//Item quantities
//used in conjunction with the Nextion HMI to track and dispense orders
int A = 0;        //Item Selection A (Round Container with Blue Material)
int B = 0;        //Item Selection B (Round Container with Red Material)
int C = 0;        //Item Selection C (Square Container with Blue Material)
int D = 0;        //Item Selection D (Square Container with Red Material)
int sum = 0;      //Sum of the total items selected for an order from the HMI (Used for Tracking how many items have been ordered/fullfilled)
int orderNo = 0;  //used to track the order number being used by the nextion

int dispensed = 0;  //Used for tracking how many containers have been dispensed
int conSent = 0;    //used for tracking how many containers have been sent to the material dispenser from the container queue
int stmCount = 0;   //keeps track of how many times a function has been called, using it for error tracking

//Handles the cases for main program
char casevar = 0;

//informative only - tracks the state of valves
bool g2Active = false;    //G1-Acturator/Square container set to being in the de-activated position
bool g1Active = false;    //G2-Actuator/Round container set to being in the de-activated position
bool dr1bActive = false;  //DR1-Gate Acutator set to being in the de-active postion

//Names should be changed as theses are confusing and not reflecting what they are controlling.
//All other vairable names are fairly self explanitory
bool irSensor1 = false;  //IR sensor1 True when container detected, false when no container detected.  First Sensor after Container Dispensor
bool irSensor2 = false;  //IR sensor2 True when container detected, false when no container detected    Sensor for queue to material dispenser
bool irSensor3 = false;  //IR sensor3 True when container detected, false when no container detected    Sensor at the material dispenser to confirm containers are their
bool irSensor4 = false;  //IR sensor4 True when container detected, false when no container detected
bool irSensor5 = false;  //IR sensor5 True when container detected, false when no container detected    Sensor at the labeler to confirm that containers are there
//bool irSensor6 = false;                                                                      //IR sensor6 True when container detected, false when no container detected
bool irstatearray[] = { irSensor1, irSensor2, irSensor3, irSensor4, irSensor5 };  //Array containing the line IR sensors values.

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
float volts1;             //used to calculate the distance the IR is reading
float distance1;          //Distance the IR is reading
float detectValue1 = 11;  //Sensor reading Value that the detect is measured against to trigger logic
float detectUpper1 = 150;

//See discriptions above for variable function
//IR Sensor 2
float volts2;
float distance2;
float detectValue2 = 14;
float detectUpper2 = 100;

//IR Sensor 3
float volts3;
float distance3;
float detectValue3 = 9;
float detectUpper3 = 500;

//IR Sensor 4
float volts4;
float distance4;
float detectValue4 = 16;
float detectUpper4 = 100;

//IR Sensor 5
float volts5;
float distance5;
float detectValue5 = 15;
float detectUpper5 = 100;

//IR Sensor 6
float volts6;
float distance6;
float detectValue6 = 16;
float detectUpper6 = 45;

int cal = 2;  //Calibration factor for finding distances

//Matrix[y][x] size to help with logic (Make sure it matches irSensorM)
int y = 5;  //rows of matrix
int x = 4;  //columns of matrix

//Matrix containing all the values that the IR sensors need to operate collect (Make sure it matches variables y & x)
float irSensorM[5][4] = {
  { volts1, distance1, detectValue1, detectUpper1 },
  { volts2, distance2, detectValue2, detectUpper2 },
  { volts3, distance3, detectValue3, detectUpper3 },
  { volts4, distance4, detectValue4, detectUpper4 },
  { volts5, distance5, detectValue5, detectUpper5 },
  //{ volts6, distance6, detectValue6, detectUpper6 }
};


//variables used in sensor calibration [Tab A31]

//ir#min is minumum distance the sensor has read during calibration
//ir#avg is the variable that is used to hold and calcualte the average value of all the readings being done duirng calibration
//ir#max is the variable that holds the highest value that is read.  during sensor calibration

float ir1min;
float ir1max;
float ir1avg;

float ir2min;
float ir2max;
float ir2avg;

float ir3min;
float ir3max;
float ir3avg;

float ir4min;
float ir4max;
float ir4avg;

float ir5min;
float ir5max;
float ir5avg;

//Arrays to hold the value of each varible during the sensor calibration
float irAVG[] = {ir1avg, ir2avg, ir3avg, ir4avg, ir5avg};
float irMin[] = {ir1min, ir2min, ir3min, ir4min, ir5min};
float irMax[] = {ir1max, ir2max, ir3max, ir4max, ir5max};

unsigned long calibrationStart;             //used for the timing of Sensor calibration 
unsigned long calibrationDuration = 5000;   //Used to be the duration of the Sensot Calibration

float totalValue = 0;     //Varaible used as the total in the averaging function
float numReadings = 0;    //The number of readings taken during sensor calibration
float sensorReadingValue = 0;   //the value to store the current IR sensor readings during Calibration

