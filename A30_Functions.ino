void setupIO() {  //InitiALIZES ALL THE DIGITAL PINS
  pinMode(reedSw1, INPUT_PULLUP);
  pinMode(reedSw2, INPUT_PULLUP);
  pinMode(contdispSqg2, OUTPUT);
  pinMode(contdispCirg1, OUTPUT);
  pinMode(contLockl1, OUTPUT);
  pinMode(actuatorL2, OUTPUT);
  pinMode(actuatorL3, OUTPUT);
  pinMode(bbdispOutgatel4, OUTPUT);
  pinMode(bbdispReddr1a, OUTPUT);
  pinMode(bbdispBludr1b, OUTPUT);
  pinMode(labelGatel5, OUTPUT);
  pinMode(labelRotr1, OUTPUT);
  pinMode(labelApplg3, OUTPUT);
  pinMode(labelAppvacv1, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(conveyors, OUTPUT);
  pinMode(endGatel6, OUTPUT);
  pinMode(labelGatel5, OUTPUT);
}

void initialize() {  //Set All the Relays to their neutral off position
  digitalWrite(contdispSqg2, HIGH);
  digitalWrite(contdispCirg1, HIGH);
  digitalWrite(contLockl1, HIGH);
  digitalWrite(actuatorL2, HIGH);
  digitalWrite(actuatorL3, HIGH);
  digitalWrite(bbdispOutgatel4, HIGH);
  digitalWrite(bbdispReddr1a, HIGH);
  digitalWrite(bbdispBludr1b, HIGH);
  digitalWrite(labelRotr1, HIGH);
  digitalWrite(labelApplg3, HIGH);
  digitalWrite(labelAppvacv1, HIGH);
  digitalWrite(conveyors, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(labelGatel5, HIGH);
  digitalWrite(endGatel6, HIGH);
}

void conveyorStart() {  //simple function that starts system conveyors.
  Serial.println("conveyor start");
  digitalWrite(conveyors, LOW);  //low is GND wich closes the relay circuit. LOW is ON for the relay
}

void conveyorStop() {  //simple function that turns the system conveyors off
  Serial.println("conveyor stop");
  digitalWrite(conveyors, HIGH);  //High is off
}

void redLEDon() {  //Simple Function to turn the Red light on the HMI enclosure on
  Serial.println("Red LED on");
  digitalWrite(redLED, LOW);  //High is off.
}

void redLEDoff() {  //Simple Function to the Red light on the HMI enclosure off
  Serial.println("Red LED off");
  digitalWrite(redLED, HIGH);  //High is off
}
void greenLEDon() {  //Simple Function to turn the Green light on the HMI enclosure on
  Serial.println("green LED on");
  digitalWrite(greenLED, LOW);  //High is off
}

void greenLEDoff() {  //Simple Function to turn the Green light on the HMI enclosure off
  Serial.println("Green LED off");
  digitalWrite(greenLED, HIGH);  //High is off
}

void redLEDslowFlash(int numBlinks) {    //millis function that flashes the Red LED on the HMI.  Pass it the number of blinks you want.
  for (int i = 0; i < numBlinks; i++) {  //Blink number of times that is passed to it
    ledpreviousMillis = millis();
    while (ledpreviousMillis + ledslowDelay > ledcurrentMillis) {  //Blink at the speed in milliseconds declared in variable on [Tab A20]
      irRefresh();                                                 //updates sensors
      digitalWrite(redLED, LOW);                                   //Turn on Red LED on HMI control Box
      ledcurrentMillis = millis();                                 //update to current time
    }
    ledpreviousMillis = millis();                                  //update to current time
    while (ledpreviousMillis + ledslowDelay > ledcurrentMillis) {  //Blink at the speed in milliseconds declared in variable on [Tab A20]
      irRefresh();                                                 //update sensors
      digitalWrite(redLED, HIGH);                                  //Turn off Red LED on HMI control Box
      ledcurrentMillis = millis();                                 //Update to current Time
    }
  }
}
void redLEDfastFlash(int numBlinks) {    //millis function that flashes the Red LED on the HMI.  Pass it the number of blinks you want.
  for (int i = 0; i < numBlinks; i++) {  //Blink number of times that is passed to it
    ledpreviousMillis = millis();
    while (ledpreviousMillis + ledfastDelay > ledcurrentMillis) {  //Blink at the speed in milliseconds declared in variable on [Tab A20]
      irRefresh();                                                 //updates sensors
      digitalWrite(redLED, LOW);                                   //Turn on Red LED on HMI control Box
      ledcurrentMillis = millis();                                 //update to current time
    }
    ledpreviousMillis = millis();                                  //update time
    while (ledpreviousMillis + ledfastDelay > ledcurrentMillis) {  //Blink at the speed in milliseconds declared in variable on [Tab A20]
      irRefresh();                                                 //updates sensors
      digitalWrite(redLED, HIGH);                                  //Turn off Red LED on HMI control Box
      ledcurrentMillis = millis();                                 //Update to current Time
    }
  }
}

void greenLEDslowFlash(int numBlinks) {  //millis function that flashes the Green LED on the HMI.  Pass it the number of blinks you want.
  for (int i = 0; i < numBlinks; i++) {  //Blink number of times that is passed to it
    ledpreviousMillis = millis();
    while (ledpreviousMillis + ledslowDelay > ledcurrentMillis) {  //Blink at the speed in milliseconds declared in variable on [Tab A20]
      irRefresh();                                                 //updates sensors
      digitalWrite(greenLED, LOW);                                 //Turn on Green LED on HMI control Box
      ledcurrentMillis = millis();                                 //update to current time
    }
    ledpreviousMillis = millis();                                  //update time
    while (ledpreviousMillis + ledslowDelay > ledcurrentMillis) {  //Blink at the speed in milliseconds declared in variable on [Tab A20]
      irRefresh();                                                 //updates sensors
      digitalWrite(greenLED, HIGH);                                //Turn off Green LED on HMI control Box
      ledcurrentMillis = millis();                                 //Update to current Time
    }
  }
}

void greenLEDfastFlash(int numBlinks) {  //millis function that flashes the Green LED on the HMI.  Pass it the number of blinks you want.
  for (int i = 0; i < numBlinks; i++) {  //Blink number of times that is passed to it
    ledpreviousMillis = millis();
    while (ledpreviousMillis + ledfastDelay > ledcurrentMillis) {  //Blink at the speed in milliseconds declared in variable on [Tab A20]
      irRefresh();                                                 //updates sensors
      digitalWrite(greenLED, LOW);                                 //Turn on Green LED on HMI control Box
      ledcurrentMillis = millis();                                 //update to current time
    }
    ledpreviousMillis = millis();                                  //update time
    while (ledpreviousMillis + ledfastDelay > ledcurrentMillis) {  //Blink at the speed in milliseconds declared in variable on [Tab A20]
      irRefresh();                                                 //updates sensors
      digitalWrite(greenLED, HIGH);                                //Turn off Green LED on HMI control Box
      ledcurrentMillis = millis();                                 //Update to current Time
    }
  }
}

void dispContsq() {                                             //Function to dispense the square container
  Serial.println("Dispensing Square Container");                //prints the action in the serial
  g2previousMillis = millis();                                  //update the the timing variable [Tab A20]
  while (g2previousMillis + dispcontDelay > g2currentMillis) {  //activate the G2 actuator and hold activated position for a varaible time dispcontDelay [Tab A20]
    irRefresh();                                                //update sensors
    g2Active = true;                                            //for keeping track of the active state of actuator,  information only [Tab A20]
    digitalWrite(contdispSqg2, LOW);                            //activate the G2 Actutator
    g2currentMillis = millis();                                 //up date the time variable [Tab A20]
  }
  g2Active = false;                  //for keeping track of the active state if actuator,  unformative only
  digitalWrite(contdispSqg2, HIGH);  //deactivate the G2 Actuator
  nextContainer();
}

void dispContcirc() {                                           //Function for dispensing the ound containers
  Serial.println("Dispensing Circular Container");              //prints the action in the serial
  g1previousMillis = millis();                                  //update the the timing variable [Tab A20]
  while (g1previousMillis + dispcontDelay > g1currentMillis) {  //activate the G1 actuator and hold activated position for a varaible time dispcontDelay [Tab A20]
    irRefresh();                                                //update sensors
    g1Active = true;                                            //for keeping track of the active state of actuator,  information only [Tab A20]
    digitalWrite(contdispCirg1, LOW);                           //activate the G1 Actutator
    g1currentMillis = millis();                                 //up date the time variable [Tab A20]
  }
  g2Active = false;                   //for keeping track of the active state of actuator,  information only [Tab A20]
  digitalWrite(contdispCirg1, HIGH);  //deactibate the G1 Actuator
  nextContainer();
}



void feedtoLabler() {  //Sends filled containers down the conveyor to the labeler station
  irRefresh();
  Serial.println("Feeding to Labler");
  Serial.println(irSensor3);       //Prints reading of the IRsensor 3 is detecting something
  digitalWrite(actuatorL3, LOW);   //Open the gate, Triggers L4 Actuator to release container
  delay(containerDelay);           //wait for the container to clear the gate
  digitalWrite(actuatorL3, HIGH);  //Close the gate, L4 Actuator to prevent containers from passing
}

void applyLabel() {  //Apply label function
  Serial.println("Label application process");
  Serial.println("Checking for container");
  //update the following code with the proper IR sensor index
  while (irstatearray[5] == 0) {  //Checks to make sure container is in position and that IR sensors 3 detects it [Tab A20]
    irRefresh();                  //update sensors [Tab A31]
    delay(irsensDelay);           //A delay that slows down the updating of IRsensors to help them be more reliable with their detection [Tab A20]
    Serial.println("ERROR: NO Container detected");
  }
  Serial.println("Container detected");
  digitalWrite(labelGatel5, LOW);     //Closes the labelergate
  delay(containerDelay);              //wait for the container to reach the labeler target location.
  digitalWrite(labelRotr1, LOW);      //rotates the label applicator to the label printer orientation.
  delay(applylblDelay);               //wait until the labeler components finish their actions.
  digitalWrite(labelApplg3, LOW);     //extends the applicator to the printer
  delay(applylblDelay);               //wait until the labeler components finish their actions.
  digitalWrite(labelAppvacv1, LOW);   //starts the vacuum.
  delay(applylblDelay);               //wait until the labeler components finish their actions.
  digitalWrite(labelApplg3, HIGH);    //retracts the applicator.
  delay(applylblDelay);               //wait until the labeler components finish their actions.
  digitalWrite(labelRotr1, HIGH);     //rotates the label applicator to the container orientation.
  delay(applylblDelay);               //wait until the labeler components finish their actions.
  digitalWrite(labelApplg3, LOW);     //extends the applicator to the container.
  delay(applylblDelay);               //wait until the labeler components finish their actions.
  digitalWrite(labelAppvacv1, HIGH);  //stop the vacuum.
  digitalWrite(labelApplg3, HIGH);    //retracts the applicator.
  delay(applylblDelay / 2);           //wait until the labeler components finish their actions.
  digitalWrite(labelGatel5, HIGH);    //Opens the labelergate.
  delay(containerDelay);              //wait the container to clear the gate
}

void checkOrder() {  //A function that reads the Nextion HMI Order status
  Serial.println("Checking order");
  A = myNex.readNumber("n2.val");  //Arduino checks how many item A (Blue material w/Round Container)was ordered on the HMI and saves it to a variable that is handled by the arduino [Tab A20]
  B = myNex.readNumber("n3.val");  //Arduino checks how many item B (Red material w/Round Container)was ordered on the HMI and saves it to a variable that is handled by the arduino [Tab A20]
  C = myNex.readNumber("n4.val");  //Arduino checks how many item C (Blue material w/Square Container)was ordered on the HMI and saves it to a variable that is handled by the arduino [Tab A20]
  D = myNex.readNumber("n5.val");  //Arduino checks how many item D (Red material w/Square Container)was ordered on the HMI and saves it to a variable that is handled by the arduino [Tab A20]
  Serial.print(A);                 //Print number of item A (Blue material w/Round Container)was ordered
  Serial.print(" , ");
  Serial.print(B);  //Print number of item B (Red material w/Round Container)was ordered
  Serial.print(" , ");
  Serial.print(C);  //Print number of item C (Blue material w/Square Container)was ordered
  Serial.print(" , ");
  Serial.print(D);  //Print number of item D (Red material w/Square Container)was ordered
  Serial.print(" , ");
  sum = A + B + C + D;  //Adds together the total number of items in the order
  Serial.println(sum);  //Prints total number of items in the order
}

void executeOrder() {                    //Large function for fullfilling the orders recieved from the HMI
  Serial.println("Executing order 66");  //Prints to serial the function of the order from HMI being fullfilled while also secretly activating the secret Galactic Republic contigency order to execute all jedi.
  conveyorStart();                       //Starts Conveyors
  containerDispensing();                 //Dispenses the containers that were ordered [Tab A30]
  materialDispensing();                  //Fills Dispensed contaiers with the correct material [Tab A30]
}

void systemsCheck() {  //Turn on and off all relays in the system
  digitalWrite(contdispSqg2, HIGH);
  digitalWrite(contdispCirg1, HIGH);
  digitalWrite(contLockl1, HIGH);
  digitalWrite(actuatorL2, HIGH);
  digitalWrite(actuatorL3, HIGH);
  digitalWrite(bbdispOutgatel4, HIGH);
  digitalWrite(bbdispReddr1a, HIGH);
  digitalWrite(bbdispBludr1b, HIGH);
  digitalWrite(labelRotr1, HIGH);
  digitalWrite(labelApplg3, HIGH);
  digitalWrite(labelAppvacv1, HIGH);
  digitalWrite(conveyors, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(labelGatel5, HIGH);
  digitalWrite(endGatel6, HIGH);
  delay(2000);
  digitalWrite(contdispSqg2, LOW);
  digitalWrite(contdispCirg1, LOW);
  digitalWrite(contLockl1, LOW);
  digitalWrite(actuatorL2, LOW);
  digitalWrite(actuatorL3, LOW);
  digitalWrite(bbdispOutgatel4, LOW);
  digitalWrite(bbdispReddr1a, LOW);
  digitalWrite(bbdispBludr1b, LOW);
  digitalWrite(labelRotr1, LOW);
  digitalWrite(labelApplg3, LOW);
  digitalWrite(labelAppvacv1, LOW);
  digitalWrite(conveyors, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(labelGatel5, LOW);
  digitalWrite(endGatel6, LOW);
  delay(2000);
  digitalWrite(contdispSqg2, HIGH);
  digitalWrite(contdispCirg1, HIGH);
  digitalWrite(contLockl1, HIGH);
  digitalWrite(actuatorL2, HIGH);
  digitalWrite(actuatorL3, HIGH);
  digitalWrite(bbdispOutgatel4, HIGH);
  digitalWrite(bbdispReddr1a, HIGH);
  digitalWrite(bbdispBludr1b, HIGH);
  digitalWrite(labelRotr1, HIGH);
  digitalWrite(labelApplg3, HIGH);
  digitalWrite(labelAppvacv1, HIGH);
  digitalWrite(conveyors, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(labelGatel5, HIGH);
  digitalWrite(endGatel6, HIGH);
  delay(2000);
}


void primePneumatics() {  //Call to Activate to indivdually fire all the pneumatics and relays to test the system and get air in all the lines
  //Make sure all relays are off/ pneumatics set to neutral
  Serial.println("Start Priming Function");
  digitalWrite(contdispSqg2, HIGH);
  digitalWrite(contdispCirg1, HIGH);
  digitalWrite(contLockl1, HIGH);
  digitalWrite(actuatorL2, HIGH);
  digitalWrite(actuatorL3, HIGH);
  digitalWrite(bbdispOutgatel4, HIGH);
  digitalWrite(bbdispReddr1a, HIGH);
  digitalWrite(bbdispBludr1b, HIGH);
  digitalWrite(labelRotr1, HIGH);
  digitalWrite(labelApplg3, HIGH);
  digitalWrite(labelAppvacv1, HIGH);
  digitalWrite(conveyors, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(labelGatel5, HIGH);
  digitalWrite(endGatel6, HIGH);
  Serial.println("G1");
  delay(primeDelay);
  //Turn each relay on and off again
  //G1 Round container dispenser
  digitalWrite(contdispCirg1, LOW);
  delay(primeDelay);
  digitalWrite(contdispCirg1, HIGH);
  Serial.println("G2");
  delay(primeDelay);
  //G2 Square Container Dispenser
  digitalWrite(contdispSqg2, LOW);
  delay(primeDelay);
  digitalWrite(contdispSqg2, HIGH);
  Serial.println("L1");
  delay(primeDelay);
  //L1 container Clamp
  digitalWrite(contLockl1, LOW);
  delay(primeDelay);
  digitalWrite(contLockl1, HIGH);
  Serial.println("L2");
  delay(primeDelay);
  // L2 Holding Gate
  digitalWrite(actuatorL2, LOW);
  delay(primeDelay);
  digitalWrite(actuatorL2, HIGH);
  Serial.println("L3");
  delay(primeDelay);
  // L3 Material Dispencer holding gate
  digitalWrite(actuatorL3, LOW);
  delay(primeDelay);
  digitalWrite(actuatorL3, HIGH);
  Serial.println("L4");
  delay(primeDelay);
  //L4 labeler holding gate
  digitalWrite(bbdispOutgatel4, LOW);
  delay(primeDelay);
  digitalWrite(bbdispOutgatel4, HIGH);
  Serial.println("DR1a &DR1b");
  delay(primeDelay);
  //DR1 opens both valves so it shouldn't move from neutral postion this is for when material is in the hoppers to make sure it doesnt spill but still puts air in the line
  digitalWrite(bbdispReddr1a, LOW);
  digitalWrite(bbdispBludr1b, LOW);
  delay(primeDelay);
  digitalWrite(bbdispReddr1a, HIGH);
  digitalWrite(bbdispBludr1b, HIGH);
  Serial.println("R1");
  delay(primeDelay);
  //R1 rotates the labeler actuator
  digitalWrite(labelRotr1, LOW);
  delay(primeDelay);
  digitalWrite(labelRotr1, HIGH);
  Serial.println("G3");
  delay(primeDelay);
  //G3 Fires the Label Grabing Actuator
  digitalWrite(labelApplg3, LOW);
  delay(primeDelay);
  digitalWrite(labelApplg3, HIGH);
  Serial.println("V1");
  delay(primeDelay);
  //V1 fires vaccum for grabbing labels
  digitalWrite(labelAppvacv1, LOW);
  delay(primeDelay);
  digitalWrite(labelAppvacv1, HIGH);
  Serial.println("L5");
  delay(primeDelay);
  //L5 Fires the actuator that holds containers at the labeler
  digitalWrite(labelGatel5, LOW);
  delay(primeDelay);
  digitalWrite(labelGatel5, HIGH);
  Serial.println("L6");
  delay(primeDelay);
  //L6 Fires the end of line actuator
  digitalWrite(endGatel6, LOW);
  delay(primeDelay);
  digitalWrite(endGatel6, HIGH);
  Serial.println("End of Priming");
}


void containerDispensing() {  //Function that fulfills the dispensing of containers ordered from the HMI
  dispensed = 0;              //Sets the variable to tp determine how many containers have been dispenced during the order
  //For loops for container dispensing
  for (int i = 0; i < A; i++) {  //Dispences all the ordered container for Item A
    Serial.println("dispensing Item A containers");
    dispContcirc();  //calls funtion to dispense round containers [Tab A30]
  }
  for (int i = 0; i < B; i++) {  //Dispences all the ordered container for Item B
    Serial.println("dispensing Item B containers");
    dispContcirc();  //calls funtion to dispense round containers [Tab A30]
  }
  for (int i = 0; i < C; i++) {  //Dispences all the ordered container for Item C
    Serial.println("dispensing Item C containers");
    dispContsq();  //calls funtion to dispense square containers [Tab A30]
  }
  for (int i = 0; i < D; i++) {  //Dispences all the ordered container for Item D
    Serial.println("dispensing Item D containers");
    dispContsq();  //calls funtion to dispense square containers [Tab A30]
  }
  Serial.println("Container Dispensing Complete");
}

void firstContainer() {                                        //is the routine of how to handle the first container dispenced to create better flow to the system
  if (dispensed == 1) {                                        //Checks to see if the continer is the first container to be dispensed
    digitalWrite(actuatorL2, LOW);                             //Open L2
    Serial.println("First Container...Opening actuatorL2");    //Updates the serial monitor to what function is called and the action
    firstConState = true;                                      //Sets the state to say that the first container is sent to the material dispenser [Tab A20]
    while (irstatearray[1] == false) {                         //holds in the function while Ir Sensor 2 doesnt detect anything
      irRefresh();                                             //update sensors
      if (irstatearray[1] == true && lastStateIR2 == false) {  //Checks if irSensor 2 detects a container on the rising edge
        printIR();
        clearanceTimer = millis();                             //update clearance timer
        Serial.println("Clearing L2");                         // update Serial Monitor
        while (millis() - clearanceTimer <= clearanceWait) {   //wait while containor passes L2 gate [Tab A20]
        }
        digitalWrite(actuatorL2, HIGH);       //Close L2
        Serial.println("actuatorL2 Closed");  //update Serial Mointor
        return;                               //returns to nextContainer Function [Tab A30]
      }
      lastStateIR2 = irstatearray[1];  //Update the last state of IR sensor 2.
    }
    Serial.println("firstContainer Function Exit error");  //Serial Monitor update for error checking
  }
  //Serial.println("not First container");  //Iff error occurs it updates the serial monitor
}

void nextContainer() {                         //controlles the timing of dispensing to be based on if irsenor 1 detects a container
  if (dispensed != sum) {                      //Checks to make sure that not all containers have been dispensed
    Serial.println("nextContainer Function");  //Updates Serial Monitor with the function
    while (irstatearray[0] == false) {
      irRefresh();                                             //update sensors
      if (irstatearray[0] == true && lastStateIR1 == false) {  //Checks if irSensor 1 detects a container
        dispensed++;                                           //Adds to the count for containers dispensed [Tab A20]
        Serial.print("Container ");                            //Feedback to the serial monitor which container has been detected by irScontDisp [Tab 10]
        Serial.print(dispensed);                               //Number of Containers detected
        Serial.print("/");                                     //Serial monitor update
        Serial.print(sum);                                     //Number of Containers ordered
        Serial.println(" detected");                           //Feedback to the serial monitor which container has been detected by irScontDisp [Tab 10]
        firstContainer();                                      //Checks uf the first container has pasted IRsensor2 [Tab A30]
        return;                                                //returns to the containerDispensing Function [Tab A30]
      }
      lastStateIR1 = irstatearray[0];  //Updates the to what the previous state of IR1
      //Serial.println("Waiting for container");  //Update Serial monitor with current status
    }
  }
  Serial.println("nextContainer Function return error [Tab 30]");  //Error Check for the Serial Monitor
}


void errorState() {  //Used to detect if containers get stuck or fail to be dispenced
}



void materialDispensing() {
  conSent = 0;   //makes sure that the containers sent to be filled is at zero
  stmCount = 0;  //Makes sure that sendToMAterial call count is zero.  used for trouble shooting
  //For loops for material dispensing
  for (int i = 0; i < A; i++) {  //Dispenses material into corresponding container for item A
    Serial.println("Dispensing material for Item A");
    if(firstConState == true){
      sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
      }      
    while (irSensor3 = 0) {  //Waits for the container to be detected by IR Sensor 3 before the fill operation will commence [Tab A20]
      irRefresh();           //Update Sensors [Tab A31]
    }
    printIR();
    dispBbblue();      //Function to Dispence Blue Material [Tab A32]
   sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
    //applyLabel();                                              //A function that handles that application of the label to the container [Tab A30]
    myNex.writeNum("n1.val", myNex.readNumber("n1.val") + 1);  //Arduino updates the HMI to display the progess of the order for Item A
    myNex.writeNum("n6.val", myNex.readNumber("n6.val") + 1);  //Arduino updates the HMI to display the progess of the entire order
    delay(1500);                                               //Delay to wait between fullfilling containers
  }
  for (int i = 0; i < B; i++) {  //Dispenses material into corresponding container for item B
    Serial.println("Dispensing material for Item B");
   Serial.println("Dispensing material for Item A");
    if(firstConState == true){
      sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
      }  
    while (irSensor3 = 0) {  //Waits for the container to be detected by IR Sensor 3 before the fill operation will commence [Tab A20]
      irRefresh();           //Update Sensors [Tab A31]
    }
    printIR();
    dispBbred();       //Function to Dispence Blue Material [Tab A32]
    sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
    //applyLabel();                                              //A function that handles that application of the label to the container [Tab A30]
    myNex.writeNum("n8.val", myNex.readNumber("n8.val") + 1);  //Arduino updates the HMI to display the progess of the order for Item B
    myNex.writeNum("n6.val", myNex.readNumber("n6.val") + 1);  //Arduino updates the HMI to display the progess of the entire order
    delay(1500);                                               //Delay to wait between fullfilling containers
  }

  for (int i = 0; i < C; i++) {  //Dispenses material into corresponding container for item C
    Serial.println("Dispensing material for Item C");
    Serial.println("Dispensing material for Item A");
    if(firstConState == true){
      sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
      }  
    while (irSensor3 = 0) {  //Waits for the container to be detected by IR Sensor 3 before the fill operation will commence [Tab A20]
      irRefresh();           //Update Sensors [Tab A31]
    }
    printIR();
    dispBbblue();      //Function to Dispence Blue Material [Tab A32]
    sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
    //applyLabel();                                              //A function that handles that application of the label to the container [Tab A30]
    myNex.writeNum("n9.val", myNex.readNumber("n9.val") + 1);  //Arduino updates the HMI to display the progess of the order for Item C
    myNex.writeNum("n6.val", myNex.readNumber("n6.val") + 1);  //Arduino updates the HMI to display the progess of the entire order
    delay(1500);                                               //Delay to wait between fullfilling containers
  }

  for (int i = 0; i < D; i++) {  //Dispenses material into corresponding container for item D
    Serial.println("Dispensing material for Item D");
    Serial.println("Dispensing material for Item A");
    if(firstConState == true){
      sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
      }  
    while (irSensor3 = 0) {  //Waits for the container to be detected by IR Sensor 3 before the fill operation will commence [Tab A20]
      irRefresh();           //Update Sensors [Tab A31]
    }
    printIR();
    dispBbred();       //Function to Dispence Blue Material [Tab A32]
    sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
    //applyLabel();                                                //A function that handles that application of the label to the container [Tab A30]
    myNex.writeNum("n10.val", myNex.readNumber("n10.val") + 1);  //Arduino updates the HMI to display the progess of the order for Item D
    myNex.writeNum("n6.val", myNex.readNumber("n6.val") + 1);    //Arduino updates the HMI to display the progess of the entire order
    delay(1500);                                                 //Delay to wait between fullfilling containers
  }
  //sendToMaterial();
  Serial.println("Order finished. move to next Nexion pg.");
  Nexion1.print("page 3");        // or Serial.print("page Main");
  Nexion1.print("\xFF\xFF\xFF");  // Nextion end command
}


void sendToMaterial() {
  Serial.println("sendToMaterial Function Called");
  irRefresh();
  if (firstConState == true) {
    while (irstatearray[2] == false) {  //Ensures that the contianer is in place before filling
      irRefresh();                      //Updates IR sensors
    }
    printIR();
    firstConState = false;  //Removes the fist container Status
    conSent++;              //increase count of containers sent
    Serial.println("first container sent");
    conCount();
    return;                                                                 //returns to materialDispenser()
    Serial.println("sendToMaterial firstConState return error [Tab A30]");  //error update
  }
  if (firstConState == false && sum == 1) {  //only calls if only one container was ordered
    clearanceTimer = millis();
    digitalWrite(actuatorL3, LOW);
    while (millis() - clearanceTimer <= clearanceWait) {}
    digitalWrite(actuatorL3, HIGH);
    Serial.println("only one container");
    conCount();
    return;                                                                 //returns to materialDispenser()
    Serial.println("sendToMaterial firstConState return error [Tab A30]");  //serial monitor error checking
  }
  if (sum > 1 && conSent != (sum - 1) && irstatearray[1] == true) {  //calls if more than one container is ordered
    conSent++;                                                       //increase count of containers sent
    lockRoutine();                                                   //call the lock routine [Tab A30]
    Serial.println("multiple containers");
    conCount();
    return;                                                                        //returns to material dispenser
    Serial.println("sendToMaterial multiple containters return error [Tab A30]");  //serial monitor error checking
  }
  if (conSent == (sum - 1) && irstatearray[1] == true) {
    conSent++;
    Serial.println("last container");
    digitalWrite(actuatorL2, LOW);  //open L2
    digitalWrite(actuatorL3, LOW);  //open L3
    Serial.println("Opening the L2 and L3 for current container");
    delay(containerDelay);           //wait the container to clear the gate
    digitalWrite(actuatorL2, HIGH);  //close L2
    digitalWrite(actuatorL3, HIGH);  //close L3
    Serial.println("last container sent");
    conCount();
    return;                                                                  //returns to material dispenser
    Serial.println("sendToMaterial last container return error [Tab A30]");  //serial monitor error checking
  }
  if (conSent == sum && irstatearray[2] == true) {
    printIR();
    clearanceTimer = millis();
    digitalWrite(actuatorL3, LOW);
    while (millis() - clearanceTimer <= clearanceWait) {}
    digitalWrite(actuatorL3, HIGH);
    Serial.println("All contianer filled");
    conCount();
    return;                                                                 //return to materialDispensing()
    Serial.println("sendToMaterial firstConState return error [Tab A30]");  //serial monitor error checking
  }
  Serial.println("sendToMaterial execution Error");
}

void feedtoTgt() {                                                    //Function that controlls the L1 and L2 actuators to control the movement of container being sent to the material dispencing station
  Serial.println("Feeding container to material dispensing target");  //Serial print of the functions actions
  Serial.print(irSensor3);                                            //Print IR sensor 3 detection status [Tab A20]
  Serial.print(" , ");
  Serial.println(irSensor2);  //Print IR Sensor 2 detection status [Tab A20]
  //FIX THIS PART  (Implement counting so we know we do have a next container.)
  /*while (irSensor3 == 0 && irScontreadyst == 0) {  //logic to determine if material dispensor has a container and if the container control gate has a container
    Serial.println("Waiting for next container");       //Prints Action
    irRefresh();                                        //update sensors
    delay(irsensDelay);                                 //A delay that slows down the updating of IRsensors to help them be more reliable with their detection [Tab A20]
  }*/
  irRefresh();                    //update sensors
  delay(gateDelay * 2);           //variable delay before allowing containers to transfer [Tab A20]
  digitalWrite(contLockl1, LOW);  //lock previous container
  Serial.println("Locking next container");
  delay(gateDelay);               //wait for container to be locked
  digitalWrite(actuatorL2, LOW);  //open the gate
  Serial.println("Opening the gate for current container");
  delay(containerDelay);           //wait the container to clear the gate
  digitalWrite(actuatorL2, HIGH);  //close the gate
  Serial.println("Closing the gate for current container");
  delay(gateDelay);                //wait for gate to be closed
  digitalWrite(contLockl1, HIGH);  //unlock previous container
  Serial.println("Unlocking the next container");
  //   }
  irRefresh();  //update sensors
}

void lockRoutine() {              //A function that facilitates the lock like system to prevent too many containers being sent to the material dispenseser
  digitalWrite(contLockl1, LOW);  //lock previous container
  Serial.println("Locking queued container");
  delay(gateDelay);               //wait for container to be locked
  digitalWrite(actuatorL2, LOW);  //open L2
  digitalWrite(actuatorL3, LOW);  //open L3
  Serial.println("Opening the L2 and L3 for current containers");
  delay(containerDelay);           //wait the container to clear the gate
  digitalWrite(actuatorL2, HIGH);  //close L2
  digitalWrite(actuatorL3, HIGH);
  Serial.println("Closing the gate for current containers");
  delay(gateDelay);                //wait for gate to be closed
  digitalWrite(contLockl1, HIGH);  //unlock previous container
  Serial.println("Unlocking queued container");
}

void conCount() {
  stmCount++;
  Serial.print(conSent);
  Serial.print("/");
  Serial.print(sum);
  Serial.print("   sendToMaterial Function was called ");
  Serial.print(stmCount);
  Serial.println(" times this order");
}
