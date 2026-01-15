//Tab for Dispensing Container functions



void dispContsq() {                                             //Function to dispense the square container
  Serial.println("Dispensing Square Container");                //prints the action in the serial
  g2previousMillis = millis();                                  //update the the timing variable [Tab A20]
  while (g2previousMillis + dispcontDelay > g2currentMillis) {  //activate the G2 actuator and hold activated position for a varaible time dispcontDelay [Tab A20]
    irRefresh();                                                //update sensors
    g2Active = true;                                            //for keeping track of the active state of actuator,  information only [Tab A20]
    digitalWrite(contdispSqg2, LOW);                            //activate the G2 Actutator
    g2currentMillis = millis();                                 //up date the time variable [Tab A20]
  }
  g2Active = false;                  //for keeping track of the active state if actuator,  informative only
  digitalWrite(contdispSqg2, HIGH);  //deactivate the G2 Actuator
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
}


void containerDispensing() {  //Function that fulfills the dispensing of containers ordered from the HMI
  dispensed = 0;              //Sets the variable to tp determine how many containers have been dispenced during the order
  //For loops for container dispensing
  for (int i = 0; i < A; i++) {  //Dispences all the ordered container for Item A
    checkIR();                   //updates the readings of the IR sensors  [Tab A31]
    Serial.println("dispensing Item A containers");
    dispContcirc();   //calls funtion to dispense round containers [Tab A30]
    nextContainer();  //calls next container function [TabA34]
  }
  for (int i = 0; i < B; i++) {  //Dispences all the ordered container for Item B
    checkIR();                   //updates the readings of the IR sensors  [Tab A31]
    Serial.println("dispensing Item B containers");
    dispContcirc();   //calls funtion to dispense round containers [Tab A30]
    nextContainer();  //calls next container function [TabA34]
  }
  for (int i = 0; i < C; i++) {  //Dispences all the ordered container for Item C
    checkIR();                   //updates the readings of the IR sensors  [Tab A31]
    Serial.println("dispensing Item C containers");
    dispContsq();     //calls funtion to dispense square containers [Tab A30]
    nextContainer();  //calls next container function [TabA34]
  }
  for (int i = 0; i < D; i++) {  //Dispences all the ordered container for Item D
    checkIR();                   //updates the readings of the IR sensors  [Tab A31]
    Serial.println("dispensing Item D containers");
    dispContsq();     //calls funtion to dispense square containers [Tab A30]
    nextContainer();  //calls next container function [TabA34]
  }
  Serial.println("Container Dispensing Complete");
}


void nextContainer() {  //controlles the timing of dispensing to be based on if irsenor 1 detects a container
  Serial.println("NOTE:   nextContainer Function entered [Tab A30]");
  if (dispensed != sum) {                                                          //Checks to make sure that not all containers have been dispensed
    Serial.println("Waiting for dispensed container");                             //Updates Serial Monitor with the function
    while (irstatearray[0] == false) {                                             //wait while container moves to IR sensor 1
      irRefresh();                                                                 //update sensors
      if (irstatearray[0] == true && lastStateIR1 == false) {                      //Checks if irSensor 1 detects a container logic check to make sure that it is on the rising edge to prevent double detection
        checkIR();                                                                 //updates the readings of the IR sensors  [Tab A31]
        dispensed++;                                                               //Adds to the count for containers dispensed [Tab A20]
        Serial.print("Container ");                                                //Feedback to the serial monitor which container has been detected by irScontDisp [Tab 10]
        Serial.print(dispensed);                                                   //Number of Containers detected
        Serial.print("/");                                                         //Serial monitor update
        Serial.print(sum);                                                         //Number of Containers ordered
        Serial.println(" detected");                                               //Feedback to the serial monitor which container has been detected by irScontDisp [Tab 10]
        firstContainer();                                                          //Checks uf the first container has pasted IRsensor2 [Tab A34]
        return;                                                                    //returns to the containerDispensing Function [Tab A34]
        Serial.println("ERROR34  nextContainer Function return error [Tab A30]");  //Error Check for the Serial Monitor
      }
      lastStateIR1 = irstatearray[0];  //Updates the to what the previous state of IR1
      //Serial.println("Waiting for container");  //Update Serial monitor with current status
    }
  }
  Serial.println("ERROR3:  nextContainer Function exit error [Tab A30]");  //Error Check for the Serial Monitor
}


void firstContainer() {  //is the routine of how to handle the first container dispenced to create better flow to the system
  Serial.println("NOTE:  firstContainer Function entered...");
  if (dispensed == 1) {                                                     //Checks to see if the continer is the first container to be dispensed
    checkIR();                                                              //updates the readings of the IR sensors  [Tab A31]
    digitalWrite(actuatorL2, LOW);                                          //Open L2
    Serial.println("First Container detected at IR1, Opening actuatorL2");  //Updates the serial monitor to what function is called and the action
    firstConState = true;                                                   //Sets the state to say that the first container is sent to the material dispenser [Tab A35]
    containerOne = true;                                                    //A state varible that lets the labeler know this is the first container [Tab A20]
    while (irstatearray[1] == false) {                                      //holds in the function while Ir Sensor 2 doesnt detect anything
      irRefresh();                                                          //update sensors
      if (irstatearray[1] == true && lastStateIR2 == false) {               //Checks if irSensor 2 detects a container on the rising edge
        Serial.println("Container detected at IR2");
        checkIR();                                            //updates the readings of the IR sensors  [Tab A31]
        clearanceTimer = millis();                            //update clearance timer
        Serial.println("Clearing L2");                        // update Serial Monitor
        while (millis() - clearanceTimer <= clearanceWait) {  //wait while containor passes L2 gate [Tab A20]
        }
        digitalWrite(actuatorL2, HIGH);       //Close L2
        Serial.println("actuatorL2 Closed");  //update Serial Mointor
        return;                               //returns to nextContainer Function [Tab A30]
        Serial.println("Error10:    firstcontainer Return error");
      }
      lastStateIR2 = irstatearray[1];  //Update the last state of IR sensor 2.  to help with detecting on a rising edge
    }
    Serial.println("ERROR1:   firstContainer Function execution error");  //Serial Monitor update for error checking
  }
  if (dispensed != 1) {
    Serial.println("Container detected at IR1 Not First Container");
    Serial.println("NOTE:   safe exit from firstContainer function");
    return;
    Serial.println("ERROR11:  firstContainer return error");
  }
  Serial.println("ERROR2:   firstContainer Function Exit error ");
}
