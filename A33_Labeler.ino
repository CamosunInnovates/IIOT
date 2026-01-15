
void labelCase() {  //A function that handles the labeling and transit of the containers
  Serial.println("NOTE:    Entered LabelCase");
  labelcaseVar = sum;  //Updates the case variable to the sum of containers ordered
  Serial.print("Case Variable Set to: ");
  Serial.println(labelcaseVar);  //informs the user of the case variable
  switch (labelcaseVar) {

    case 1:  //Case one handles if only one container is ordered.  Its function is to just wait for the container to be filled and sent to the labeler.
      Serial.println("label Case 1 entered");
      Serial.println("Waiting for container at IR 5");
      while (irstatearray[4] == false) {  //Wait for container to arrive at IR sensor 5
        irRefresh();                      //Continually update the IT sensors
      }
      applyLabel();  // call the apply label function

      cycleL5();  //Open and close Actuator 5
      containerOne = false;
      break;
      Serial.println("ERROR14:   Label Case 1 Break Error");

    case 2:  //Handles when more than one container is ordered. Defualt is for two but other cases send to this function
      Serial.println("label Case 2 entered");
      if (containerOne == true) {  //Checks to see if the container is the first container
        Serial.println("Sending first container directly to labeler");
        containerOne = false;  //Set the value to flase as the next container will not be the first container
        return;
        Serial.println("ERROR15:     Labelcase 2 first container return error");
      }
      closeL4();  //Closes the L4 actuator
      Serial.println("Waiting for container at IR 5");
      while (irstatearray[4] == false) {  //Wait for the container to be detected
        irRefresh();
      }
      applyLabel();     //calls the apply label function to apply a label to the container [Tab A33]

      Serial.println("Opening Actuator L4");
      openL4();  //Opens the L4 Actuator
      digitalWrite(actuatorL5, LOW);
      delay(containerDelay);  //Clear actuator 5
      Serial.println("Closing Actuator L4");
      digitalWrite(actuatorL5, HIGH);
      while (irstatearray[4] == false) {  //Wait for container to be detected by IR Sensor 5
        irRefresh();
      }
      applyLabel();  //[Tab A33]
      cycleL5();     //open then close Actuator L5
      break;
      Serial.println("ERROR16:   Label Case 2 Break Error");


    case 3:  //Handles when 3 containers are callled (not working last time tested)
      Serial.println("label Case 3 entered");
      if (containerOne == true || sendToLabeler == sum) {  //determines if it is the first or last container  (not working last time tested)
        labelcaseVar = 2;   //Sets case variable to go to case 2
        Serial.print("Case Variable Set to: ");
        Serial.println(labelcaseVar);
        return;
        Serial.println("ERROR18:     Labelcase 3 first container return error");
      }
      closeL4(); //[Tab A33]
      holdL4 = true;  //Makes sure that the container doesnt get sent after being filled at the MD
      Serial.println("Waiting for container at IR 5");
      while (irstatearray[4] == false) {  //wait for IR Sensor 5 to detect container
        irRefresh();
      }
      applyLabel();  //[Tab A33]
      break;
      Serial.println("ERROR20:     Labelcase 3 first container return error");

    case 4:  //Called when 4 containers are ordered.....Just points to case 3.  (Not currently working)
      Serial.println("label Case 4 entered");
      labelcaseVar = 3;
      Serial.print("Case Variable Set to: ");
      Serial.println(labelcaseVar);
      return;
      Serial.println("ERROR19:     Labelcase 4 first container return error");
  }


  Serial.println("Note:   Leaving labelcase");
  return;
  Serial.println("ERROR17:     labelCase Function return error");
}




void applyLabel() {                                               //A function for dispensing and appling a label to a container
  Serial.println("Note:  Entering apply labelFunction");          //Lets us know what function we have entered
  Serial.println("Waiting for IR sensor 5 to detect Container");  //Prints the current action
  while (irstatearray[4] == 0) {                                  //Wait for sensor 5 to detect a container
    irRefresh();                                                  //Keeps sensors up to date
  }
  Serial.println("Container detected at IR sensor 5");  //Serial update
  checkIR();                                            //updates Serial with the sensor update
  labelDispensing();                                    //Calls function to dispense a label for applying
  vacuumON();
  g3Activate();  //A function to allow for extension and retraction [Tab A33]
  Serial.println("Rotating R1 90deg CCW");
  digitalWrite(rotorR1, LOW);  //Turn on Actuator
  delay(r1Delay);              //wait time [Tab A20]
  Serial.println("Extend Actuator G3");
  digitalWrite(actuatorG3, LOW);  //Turn on Actuator
  delay(g3Delay * 1.5);           //A delay to allow for extension and retraction [Tab A20]
  vacuumOFF();                    //Turn the vacuum off
  Serial.println("Retract Actuator G3");
  digitalWrite(actuatorG3, HIGH);  //Turn off Actuator
  delay(g3Delay*.75);                  //wait time [Tab A20]
  labelApplied++;                  //Increment label Applied by 1
  Serial.println("Rotating R1 90deg CW");
  digitalWrite(rotorR1, HIGH);  //Turn off Actuator
  Serial.print(labelApplied);
  Serial.print("/");
  Serial.print(sum);
  Serial.println(" Labels Applied to Containers");

  Serial.println("Note:   Exiting applyLabel Function");
  return;
  Serial.println("ERROR12:      applyLabel Function Exit Error");
}


void g3Activate() {  //A function to handle the extension and retraction of the G3 Actuator
  Serial.println("Extend Actuator G3");
  digitalWrite(actuatorG3, LOW);  //Turn on Actuator
  delay(g3Delay * 1.5);           //A delay to allow for extension and retraction [Tab A20]
  Serial.println("Retract Actuator G3");
  digitalWrite(actuatorG3, HIGH);  //Turn off Actuator
  delay(g3Delay);                  //A delay to allow for extension and retraction [Tab A20]
}

void labelDispensing() {                                      //function the wake and print the dymo 450 label printer.
  Serial.println("NOTE:   labelDispensing function called");  //updates Serial
  if (millis() - lastDispensed >= wakeDymo) {                 //The printer goes to "sleep" mode after 30 seconds from last label printed
    Serial.print("NOTE:    Waking Printer");
    analogWrite(peelLabel, 1023);  //ensuring the relay is in the neutral postion
    delay(dispenseLabelTimer);     //Wait for time
    analogWrite(peelLabel, 0);     //Set relay to low.  Labeler is awake
    delay(dispenseLabelTimer);     // wait a time
    analogWrite(peelLabel, 1023);  //Set relay back to neutral position
  }

  Serial.println("Dispensing a Label");  //updates Serial
  analogWrite(peelLabel, 1023);          //ensuring the relay is in the neutral postion
  delay(dispenseLabelTimer);             //Wait for time [Tab A20]
  analogWrite(peelLabel, 0);             //Set relay to low.  Labeler dispnces the label
  delay(dispenseLabelTimer);             //Wait for time [Tab A20]
  analogWrite(peelLabel, 1023);          //Set relay back to neutral position
  delay(dispenseLabelTimer);             //Wait for time [Tab A20]
  //digitalWrite(peelLabel, HIGH);  //Set relay back to neutral position  //not sure if the relay need to be activated via digital or if analog works
  lastDispensed = millis();  //Marks the time of the last label printed to determine if printer is in "sleep" mode
  Serial.println("NOTE:    Exiting labelDispensing Function");
  return;
  Serial.println("ERROR11:    labelDispensing function exit Error");
}



void vacuumON() {  //used to create the venturi for the vacuum
  Serial.println("Turning Vacuum on");
  digitalWrite(vacuumV1, LOW);    //Turn on Actuator
  digitalWrite(actuatorL6, LOW);  //Turns on Actuator L6 valve to allow the venting of air making the creation of a venturi
  delay(v1Delay);                 //wait time [Tab A20]
}

void vacuumOFF() {  //to turn off the vacuum for the venturi
  Serial.println("Turning Vacuum off");
  digitalWrite(vacuumV1, HIGH);    //Turn on Actuator
  digitalWrite(actuatorL6, HIGH);  //Turns on Actuator L6 valve to allow the venting of air making the creation of a venturi
  delay(v1Delay);                  //wait time [Tab A20]
}


void openL4() {  //function to add clarity and easito opening of L4
  Serial.println("Opening Actuator L4");
  digitalWrite(actuatorL4, HIGH);
  L4Closed = false;  //Sets the state of the L4 open/closed
}

void closeL4() {  //function to add clarity and simplisity to closing of L4
  Serial.println("Closung Actuator L4");
  digitalWrite(actuatorL4, LOW);
  L4Closed = true;  //Sets the state of the L4 open/closed
}

void cycleL5() {  //function to handle opening and closing for L5
  Serial.println("Opening Actuator L5");
  digitalWrite(actuatorL5, LOW);
  delay(containerDelay);
  Serial.println("Closing Actuator L5");
  digitalWrite(actuatorL5, HIGH);
}


void lastContainertoLabel() {  //A functions to handle the transiting and applying of labels after the material dispensor has filled all the containers
  Serial.println("Note:      LastContainertoLAbel Function called");
  Serial.println("Last Container has been filled");
  Serial.print("Applying Remaining Labels");
  for (int i = labelApplied; labelApplied <= sum; i++) {
    Serial.print("i value for loop = ");
    Serial.println(i);
    while (irstatearray[4] == false) {  //Wait for container to arrive at IR sensor 5
      irRefresh();                      //Continually update the IT sensors
    }
    applyLabel();  // call the apply label function
    Serial.println("Opening Actuators");  //open Actuators
    digitalWrite(actuatorL5, LOW);
    digitalWrite(actuatorL4, HIGH);
    digitalWrite(actuatorL3, LOW);
    delay(clearL4);  //Used for clearing L4 as its timer is less thatn container delay
    Serial.println("Closing Actuators");  //Close actuators
    digitalWrite(actuatorL4, LOW);
    delay(clearL4);  //wait the container to clear the gate but account for the time waited to clear L4
    digitalWrite(actuatorL5, HIGH);
    digitalWrite(actuatorL3, HIGH);
  }
  Serial.println("Exiting lastContainertoLabel");
}