/*
Tab for functions relating to material Dispensing





*/


void materialDispensing() {
  conSent = 0;               //makes sure that the containers sent to be filled is at zero
  stmCount = 0;              //Makes sure that sendToMAterial call count is zero.  used for trouble shooting
  labelApplied = 0;          //Resets the label Applied variable that helps tracking how many labels have been dispensed
  sendToLabeler = 0;         //makes sure that the containers to be sent to labeler are set to zero
  holdL4 = false;

  //For loops for material dispensing
  for (int i = 0; i < A; i++) {  //Dispenses material into corresponding container for item A
    Serial.println("Dispensing material for Item A");
    serialCheck();                //Adds an Error Check to the system needing a user to complete the next operation [Tab A30]
    if (firstConState == true) {  //A function to handle if the first container has already been sent to the material dispensing Station station
      sendToMaterial();           //Function that sends the dispensed container to the next station [Tab A30]
    }
    while (irSensor3 = 0) {  //Waits for the container to be detected by IR Sensor 3 before the fill operation will commence [Tab A20]
      irRefresh();           //Update Sensors [Tab A31]
    }
    printIR();
    dispBbblue();                                              //Function to Dispence Blue Material [Tab A32]
    sendToMaterial();                                          //Function that sends the dispensed container to the next station [Tab A30]
    sendToLabeler++;                                           //Increment variable by one to send the container to the labeling station [Tab A20]
    labelCase();                                               //A function that handles that application of the label to the container [Tab A30]
    myNex.writeNum("n1.val", myNex.readNumber("n1.val") + 1);  //Arduino updates the HMI to display the progess of the order for Item A
    myNex.writeNum("n6.val", myNex.readNumber("n6.val") + 1);  //Arduino updates the HMI to display the progess of the entire order
    delay(1500);                                               //Delay to wait between fullfilling containers
  }

  for (int i = 0; i < B; i++) {  //Dispenses material into corresponding container for item B
    Serial.println("Dispensing material for Item B");
    serialCheck();  //Adds an Error Check to the system needing a user to complete the next operation [Tab A30]
    if (firstConState == true) {
      sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
    }
    while (irSensor3 = 0) {  //Waits for the container to be detected by IR Sensor 3 before the fill operation will commence [Tab A20]
      irRefresh();           //Update Sensors [Tab A31]
    }
    printIR();
    dispBbred();                                               //Function to Dispence Blue Material [Tab A32]
    sendToMaterial();                                          //Function that sends the dispensed container to the next station [Tab A30]
    sendToLabeler++;                                           //Increment variable by one to send the container to the labeling station [Tab A20]
    labelCase();                                               //A function that handles that application of the label to the container [Tab A30]
    myNex.writeNum("n8.val", myNex.readNumber("n8.val") + 1);  //Arduino updates the HMI to display the progess of the order for Item B
    myNex.writeNum("n6.val", myNex.readNumber("n6.val") + 1);  //Arduino updates the HMI to display the progess of the entire order
    delay(1500);                                               //Delay to wait between fullfilling containers
  }

  for (int i = 0; i < C; i++) {  //Dispenses material into corresponding container for item C
    Serial.println("Dispensing material for Item C");
    serialCheck();  //Adds an Error Check to the system needing a user to complete the next operation [Tab A30]
    if (firstConState == true) {
      sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
    }
    while (irSensor3 = 0) {  //Waits for the container to be detected by IR Sensor 3 before the fill operation will commence [Tab A20]
      irRefresh();           //Update Sensors [Tab A31]
    }
    printIR();
    dispBbblue();                                              //Function to Dispence Blue Material [Tab A32]
    sendToMaterial();                                          //Function that sends the dispensed container to the next station [Tab A30]
    sendToLabeler++;                                           //Increment variable by one to send the container to the labeling station [Tab A20]
    labelCase();                                               //A function that handles that application of the label to the container [Tab A30]
    myNex.writeNum("n9.val", myNex.readNumber("n9.val") + 1);  //Arduino updates the HMI to display the progess of the order for Item C
    myNex.writeNum("n6.val", myNex.readNumber("n6.val") + 1);  //Arduino updates the HMI to display the progess of the entire order
    delay(1500);                                               //Delay to wait between fullfilling containers
  }

  for (int i = 0; i < D; i++) {  //Dispenses material into corresponding container for item D
    Serial.println("Dispensing material for Item D");
    serialCheck();  //Adds an Error Check to the system needing a user to complete the next operation [Tab A30]
    if (firstConState == true) {
      sendToMaterial();  //Function that sends the dispensed container to the next station [Tab A30]
    }
    while (irSensor3 = 0) {  //Waits for the container to be detected by IR Sensor 3 before the fill operation will commence [Tab A20]
      irRefresh();           //Update Sensors [Tab A31]
    }
    printIR();
    dispBbred();                                                 //Function to Dispence Blue Material [Tab A32]
    sendToMaterial();                                            //Function that sends the dispensed container to the next station [Tab A30]
    sendToLabeler++;                                             //Increment variable by one to send the container to the labeling station [Tab A20]
    labelCase();                                                 //A function that handles that application of the label to the container [Tab A30]
    myNex.writeNum("n10.val", myNex.readNumber("n10.val") + 1);  //Arduino updates the HMI to display the progess of the order for Item D
    myNex.writeNum("n6.val", myNex.readNumber("n6.val") + 1);    //Arduino updates the HMI to display the progess of the entire order
    delay(1500);                                                 //Delay to wait between fullfilling containers
  }
}



void sendToMaterial() {
  Serial.println("NOTE:    sendToMaterial Function Called");
  irRefresh();
  if (firstConState == true) {
    while (irstatearray[2] == false) {  //Ensures that the contianer is in place before filling
      irRefresh();                      //Updates IR sensors
    }
    checkIR();              //updates the readings of the IR sensors  [Tab A31]
    firstConState = false;  //Removes the fist container Status
    conSent++;              //increase count of containers sent
    Serial.println("first container sent");
    conCount();
    return;                                                                           //returns to materialDispenser()
    Serial.println("ERROR5:   sendToMaterial firstConState return error [Tab A30]");  //error update
    checkIR();                                                                        //updates the readings of the IR sensors  [Tab A31]
  }
  if (firstConState == false && sum == 1) {  //only calls if only one container was ordered
    clearanceTimer = millis();
    digitalWrite(actuatorL3, LOW);
    while (millis() - clearanceTimer <= clearanceWait) {}
    digitalWrite(actuatorL3, HIGH);
    Serial.println("only one container");
    conCount();
    return;                                                                            //returns to materialDispenser()
    Serial.println("ERROR6:    sendToMaterial firstConState return error [Tab A30]");  //serial monitor error checking
    checkIR();                                                                         //updates the readings of the IR sensors  [Tab A31]
  }
  checkIR();                                                         //updates the readings of the IR sensors  [Tab A31]
  if (sum > 1 && conSent != (sum - 1) && irstatearray[1] == true) {  //calls if more than one container is ordered
    conSent++;                                                       //increase count of containers sent
    lockRoutine();                                                   //call the lock routine [Tab A30]
    Serial.println("multiple containers");
    conCount();
    return;                                                                                  //returns to material dispenser
    Serial.println("ERROR7:   sendToMaterial multiple containters return error [Tab A30]");  //serial monitor error checking
    checkIR();                                                                               //updates the readings of the IR sensors  [Tab A31]
  }
  checkIR();  //updates the readings of the IR sensors  [Tab A31]
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
    return;                                                                             //returns to material dispenser
    Serial.println("ERROR8:    sendToMaterial last container return error [Tab A30]");  //serial monitor error checking
    checkIR();                                                                          //updates the readings of the IR sensors  [Tab A31]
  }
  checkIR();  //updates the readings of the IR sensors  [Tab A31]
  if (conSent == sum && irstatearray[2] == true) {  //If all containers are filled and ready to send the last one down the line
    printIR();
    clearanceTimer = millis();
    //lastContainertoLabel();
    digitalWrite(actuatorL3, LOW);
    while (millis() - clearanceTimer <= clearanceWait) {}
    digitalWrite(actuatorL3, HIGH);
    Serial.println("All contianer filled");
    conCount();
    return;                                                                            //return to materialDispensing()
    Serial.println("ERROR9:    sendToMaterial firstConState return error [Tab A30]");  //serial monitor error checking
    checkIR();                                                                         //updates the readings of the IR sensors  [Tab A31]
  }
  Serial.println("ERROR10:     sendToMaterial exit Error");
  checkIR();  //updates the readings of the IR sensors  [Tab A31]
}



void conCount() {  //function to help keep track of containers that have been sent to the material dispencer
  stmCount++;
  Serial.print(conSent);  //pronts value of variable [A20]
  Serial.print("/");
  Serial.print(sum);  //Prints total number of containers it will fill
  Serial.print("   sendToMaterial Function was called ");
  Serial.print(stmCount);  //used for error tracking to see how many times a function was call
  Serial.println(" times this order");
}
