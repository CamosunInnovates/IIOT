void setupIO() {  //InitiALIZES ALL THE DIGITAL PINS
  pinMode(reedSw1, INPUT_PULLUP);
  pinMode(reedSw2, INPUT_PULLUP);
  pinMode(contdispSqg2, OUTPUT);
  pinMode(contdispCirg1, OUTPUT);
  pinMode(contLockl1, OUTPUT);
  pinMode(actuatorL2, OUTPUT);
  pinMode(actuatorL3, OUTPUT);
  pinMode(actuatorL4, OUTPUT);
  pinMode(bbdispReddr1a, OUTPUT);
  pinMode(bbdispBludr1b, OUTPUT);
  pinMode(actuatorL5, OUTPUT);
  pinMode(rotorR1, OUTPUT);
  pinMode(actuatorG3, OUTPUT);
  pinMode(vacuumV1, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(conveyors, OUTPUT);
  pinMode(actuatorL6, OUTPUT);
  pinMode(actuatorL5, OUTPUT);
}

void initialize() {  //Set All the Relays to their neutral off position
  digitalWrite(contdispSqg2, HIGH);
  digitalWrite(contdispCirg1, HIGH);
  digitalWrite(contLockl1, HIGH);
  digitalWrite(actuatorL2, HIGH);
  digitalWrite(actuatorL3, HIGH);
  digitalWrite(actuatorL4, HIGH);
  digitalWrite(bbdispReddr1a, HIGH);
  digitalWrite(bbdispBludr1b, HIGH);
  digitalWrite(rotorR1, HIGH);
  digitalWrite(actuatorG3, HIGH);
  digitalWrite(vacuumV1, HIGH);
  digitalWrite(conveyors, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(actuatorL5, HIGH);
  digitalWrite(actuatorL6, HIGH);
}

void conveyorStart() {  //simple function that starts system conveyors.
  Serial.println("conveyor start");
  digitalWrite(conveyors, LOW);  //low is GND wich closes the relay circuit. LOW is ON for the relay
  lastDispensed = millis();  //Marks the time of the last label printed to determine if printer is in "sleep" mode.  It is placed here as the labeler is powered on when the conveyors are on
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

void serialCheck() {  //Pauses program to insure each step is being executed properly
  Serial.println();
  Serial.println("Serial Check");
  //while (Serial.available() == 0) {}  //waits for an input before coninuing
  checkIR();     //updates the readings of the IR sensors  [Tab A31]
  stateCheck();  //Check current state values for the program [Tab A30]
  Serial.println();
}



void checkOrder() {  //A function that reads the Nextion HMI Order status
  Serial.println("Checking order");
  orderNo = myNex.readNumber("n0.val");  //Arduino Checks what order number is being used ny the Nextion [Tab A20]
  A = myNex.readNumber("n2.val");        //Arduino checks how many item A (Blue material w/Round Container)was ordered on the HMI and saves it to a variable that is handled by the arduino [Tab A20]
  B = myNex.readNumber("n3.val");        //Arduino checks how many item B (Red material w/Round Container)was ordered on the HMI and saves it to a variable that is handled by the arduino [Tab A20]
  C = myNex.readNumber("n4.val");        //Arduino checks how many item C (Blue material w/Square Container)was ordered on the HMI and saves it to a variable that is handled by the arduino [Tab A20]
  D = myNex.readNumber("n5.val");        //Arduino checks how many item D (Red material w/Square Container)was ordered on the HMI and saves it to a variable that is handled by the arduino [Tab A20]
  Serial.print("Order Number: ");
  Serial.println(orderNo);  //Prints order number of the Nextion
  Serial.print(A);          //Print number of item A (Blue material w/Round Container)was ordered
  Serial.print(" , ");
  Serial.print(B);  //Print number of item B (Red material w/Round Container)was ordered
  Serial.print(" , ");
  Serial.print(C);  //Print number of item C (Blue material w/Square Container)was ordered
  Serial.print(" , ");
  Serial.print(D);  //Print number of item D (Red material w/Square Container)was ordered
  Serial.print(" , ");
  sum = A + B + C + D;  //Adds together the total number of items in the order
  Serial.println(sum);  //Prints total number of items in the order
  serialCheck();        //Adds an Error Check to the system needing a user to complete the next operation [Tab A30]
}

void executeOrder() {                    //Large function for fullfilling the orders recieved from the HMI
  Serial.println("Executing order 66");  //Prints to serial the function of the order from HMI being fullfilled while also secretly activating the secret Galactic Republic contigency order to execute all jedi.
  Serial.println();                      //creates some spacing for better organisation
  serialCheck();                         //Adds an Error Check to the system needing a user to complete the next operation [Tab A30]

  conveyorStart();  //Starts Conveyors [Tab A30]
  serialCheck();    //Adds an Error Check to the system needing a user to complete the next operation [Tab A30]

  containerDispensing();  //Dispenses the containers that were ordered [Tab A34]
  serialCheck();          //Adds an Error Check to the system needing a user to complete the next operation

  materialDispensing();  //Fills Dispensed contaiers with the correct material [Tab A35]
  serialCheck();         //Adds an Error Check to the system needing a user to complete the next operation

  endOrder();  //Communicates with the HMI to end the order
}

void systemsCheck() {  //Turn on and off all relays in the system all at once
  digitalWrite(contdispSqg2, HIGH);
  digitalWrite(contdispCirg1, HIGH);
  digitalWrite(contLockl1, HIGH);
  digitalWrite(actuatorL2, HIGH);
  digitalWrite(actuatorL3, HIGH);
  digitalWrite(actuatorL4, HIGH);
  digitalWrite(bbdispReddr1a, HIGH);
  digitalWrite(bbdispBludr1b, HIGH);
  digitalWrite(rotorR1, HIGH);
  digitalWrite(actuatorG3, HIGH);
  digitalWrite(vacuumV1, HIGH);
  digitalWrite(conveyors, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(actuatorL5, HIGH);
  digitalWrite(actuatorL6, HIGH);
  delay(2000);
  digitalWrite(contdispSqg2, LOW);
  digitalWrite(contdispCirg1, LOW);
  digitalWrite(contLockl1, LOW);
  digitalWrite(actuatorL2, LOW);
  digitalWrite(actuatorL3, LOW);
  digitalWrite(actuatorL4, LOW);
  digitalWrite(bbdispReddr1a, LOW);
  digitalWrite(bbdispBludr1b, LOW);
  digitalWrite(rotorR1, LOW);
  digitalWrite(actuatorG3, LOW);
  digitalWrite(vacuumV1, LOW);
  digitalWrite(conveyors, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(actuatorL5, LOW);
  digitalWrite(actuatorL6, LOW);
  delay(2000);
  digitalWrite(contdispSqg2, HIGH);
  digitalWrite(contdispCirg1, HIGH);
  digitalWrite(contLockl1, HIGH);
  digitalWrite(actuatorL2, HIGH);
  digitalWrite(actuatorL3, HIGH);
  digitalWrite(actuatorL4, HIGH);
  digitalWrite(bbdispReddr1a, HIGH);
  digitalWrite(bbdispBludr1b, HIGH);
  digitalWrite(rotorR1, HIGH);
  digitalWrite(actuatorG3, HIGH);
  digitalWrite(vacuumV1, HIGH);
  digitalWrite(conveyors, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(actuatorL5, HIGH);
  digitalWrite(actuatorL6, HIGH);
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
  digitalWrite(actuatorL4, HIGH);
  digitalWrite(bbdispReddr1a, HIGH);
  digitalWrite(bbdispBludr1b, HIGH);
  digitalWrite(rotorR1, HIGH);
  digitalWrite(actuatorG3, HIGH);
  digitalWrite(vacuumV1, HIGH);
  digitalWrite(conveyors, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(actuatorL5, HIGH);
  digitalWrite(actuatorL6, HIGH);
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
  digitalWrite(actuatorL4, LOW);
  delay(primeDelay);
  digitalWrite(actuatorL4, HIGH);
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
  digitalWrite(rotorR1, LOW);
  delay(primeDelay);
  digitalWrite(rotorR1, HIGH);
  Serial.println("G3");
  delay(primeDelay);
  //G3 Fires the Label Grabing Actuator
  digitalWrite(actuatorG3, LOW);
  delay(primeDelay);
  digitalWrite(actuatorG3, HIGH);
  Serial.println("V1");
  delay(primeDelay);
  //V1 fires vaccum for grabbing labels
  digitalWrite(vacuumV1, LOW);
  delay(primeDelay);
  digitalWrite(vacuumV1, HIGH);
  Serial.println("L5");
  delay(primeDelay);
  //L5 Fires the actuator that holds containers at the labeler
  digitalWrite(actuatorL5, LOW);
  delay(primeDelay);
  digitalWrite(actuatorL5, HIGH);
  Serial.println("L6");
  delay(primeDelay);
  //L6 Fires the end of line actuator
  digitalWrite(actuatorL6, LOW);
  delay(primeDelay);
  digitalWrite(actuatorL6, HIGH);
  Serial.println("End of Priming");
}

void errorState() {  //Used to detect if containers get stuck or fail to be dispenced
}



void lockRoutine() {  //A function that facilitates the lock like system to prevent too many containers being sent to the material dispenseser
  Serial.println("NOTE:    lockRoutine Function Entered");
  digitalWrite(contLockl1, LOW);  //lock previous container
  Serial.println("Locking queued container");
  delay(gateDelay);               //wait for container to be locked
  digitalWrite(actuatorL2, LOW);  //open L2
  digitalWrite(actuatorL3, LOW);  //open L3
  if (holdL4 == true) {           //If a Container is at the label Station Open L5 and L4
    digitalWrite(actuatorL5, LOW);
    digitalWrite(actuatorL4, HIGH);
    delay(clearL4);  //Used for clearing L4 as its timer is less thatn container delay
    digitalWrite(actuatorL4, LOW);
    delay(containerDelay - clearL4);  //wait the container to clear the gate but account for the time waited to clear L4
  } else {
    Serial.println("Opening the L2 and L3 for current containers");
    delay(containerDelay);  //wait the container to clear the gate
  }
  digitalWrite(actuatorL2, HIGH);  //close L2
  digitalWrite(actuatorL3, HIGH);  //close L3
  digitalWrite(actuatorL5, HIGH);  //close L5
  Serial.println("Closing the gates for current containers");
  delay(gateDelay);                //wait for gate to be closed
  digitalWrite(contLockl1, HIGH);  //unlock previous container
  Serial.println("Unlocking queued container");
  Serial.println("NOTE:    lockRoutine Function exited");
}

void stateCheck() {  //Function to check the state of each sensor and actuator
  Serial.println(" ");
  //order variables
  Serial.print("Current Order Values: A = ");
  Serial.print(A);
  Serial.print(", B = ");
  Serial.print(B);
  Serial.print(", C = ");
  Serial.print(C);
  Serial.print(", D = ");
  Serial.print(D);
  Serial.print(", sum = ");
  Serial.println(sum);


  //State variables
  Serial.print("Current State Values: filledState = ");
  Serial.print(filledState);
  Serial.print(", firstConState = ");
  Serial.print(firstConState);
  Serial.print(", dispConState = ");
  Serial.print(dispConState);
  Serial.print(", l2State = ");
  Serial.print(l2State);
  Serial.print(", nextCon = ");
  Serial.print(nextCon);
  Serial.print(", clearanceState = ");
  Serial.print(clearanceState);
  Serial.print(", containerOne = ");
  Serial.print(containerOne);
  Serial.print(", holdL4 = ");
  Serial.println(holdL4);




  //Count Values
  Serial.print("Current Count Values: dispensed = ");
  Serial.print(dispensed);
  Serial.print("/");
  Serial.print(sum);
  Serial.print(", conSent = ");
  Serial.print(conSent);
  Serial.print("/");
  Serial.print(sum);
  Serial.print(", stmCount = ");
  Serial.print(stmCount);
  Serial.print("/");
  Serial.print(sum + 1);
  Serial.print(", sendToLabeler = ");
  Serial.print(sendToLabeler);
  Serial.print("/");
  Serial.print(sum);
  Serial.print(", labelApplied = ");
  Serial.print(labelApplied);
  Serial.print("/");
  Serial.println(sum);



  //IR INFO
  // Serial.println("IR Matrix Values:");
  // for (int j = 0; j < y; j++) {       // Iterate through rows
  //   for (int i = 0; i < x; i++) {     // Iterate through columns
  //     Serial.print(irSensorM[j][i]);  // Print the element
  //     Serial.print("\t");             // Print a tab for spacing
  //   }
  //   Serial.println("");  // Move to the next line after each row
  // }
  Serial.println("");
}



void endOrder() {  //A function to complete the order.  This communicates back to the HMI that the order is complete
  Serial.println("Order finished. move to next Nexion pg.");
  Nexion1.print("page 3");        // or Serial.print("page Main");
  Nexion1.print("\xFF\xFF\xFF");  // Nextion end command
}


