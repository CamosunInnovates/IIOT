void dispBbblue() {    // Function that handles the despencing of blue material into their containers
  delay(dispbbDelay);  //Delay that allows for the container to be positioned under the feed tube fully after detected by IR sensor 3 [Tab A20]
  Serial.println("Dispensing Blue BBs");
  while (irstatearray[2] == 0) {  //Checks to make sure container is in position and that IR sensors 3 detects it [Tab A20]
    irRefresh();                  //update sensors [Tab A31]
    delay(irsensDelay);           //A delay that slows down the updating of IRsensors to help them be more reliable with their detection [Tab A20]
  }
  printIR();
  digitalWrite(bbdispBludr1b, LOW);  //Move Gate to the side
  Serial.println("Blue Opening");
  delay(blueGateTimer);                       //Delays for the set time to allow bbs to flow [Tab A20]
  Serial.println("Blue Closing");
  while (digitalRead(reedSw1) == HIGH) {  //loop to move the gate back to neutral (Travel in opposite direction until neutral postition is achieved) [Tab A10]
    delay(blueTimeCorrection);                //Extra time need move the gate into proper postion [Tab A10]
    digitalWrite(bbdispReddr1a, LOW);     //Moves gate into the opposite direction [Tab A10]
    digitalWrite(bbdispBludr1b, HIGH);    //turns off original air direction off [Tab A10]
    
  }
  digitalWrite(bbdispBludr1b, LOW);   //Switches off return air direction [Tab A10]
  delay(250);                         //Delay to allow for smoother operation
  digitalWrite(bbdispBludr1b, HIGH);  //Ensures Air is off [Tab A10]
  digitalWrite(bbdispReddr1a, HIGH);  //turns off valve that moved gate towards neutral [Tab A10]
  delay(dispbbDelay);
}

void dispBbred() {     //Function that handles the despencing of blue material into their containers
  delay(dispbbDelay);  //Delay that allows for the container to be positioned under the feed tube fully after detected by IR sensor 3 [Tab A20]
  Serial.println("Dispensing Red BBs");
  while (irstatearray[2] == 0) {  //Checks to make sure container is in position and that IR sensors 3 detects it [Tab A20]
    irRefresh();                  //update sensors [Tab A31]
    delay(irsensDelay);           //A delay that slows down the updating of IRsensors to help them be more reliable with their detection [Tab A20]
  }
  printIR();
  //See Blue Dispence for the same logic and note its just opposite
  digitalWrite(bbdispReddr1a, LOW);
  Serial.println("Red Opening");
  delay(redGateTimer);
      Serial.println("Red Closing");
  while (digitalRead(reedSw1) == HIGH) {
    delay(redTimeCorrection);
    digitalWrite(bbdispBludr1b, LOW);
    digitalWrite(bbdispReddr1a, HIGH);

  }
  digitalWrite(bbdispReddr1a, LOW);   //Switches off return air direction [Tab A10]
  delay(250);                         //Delay to allow for smoother operation
  digitalWrite(bbdispBludr1b, HIGH);  //Ensures Air is off [Tab A10]
  digitalWrite(bbdispReddr1a, HIGH);  //turns off valve that moved gate towards neutral [Tab A10]
  delay(dispbbDelay);
}

void gateCentering() {                    //a small function to send the gate back to neutral.  DO NOT use while their are BBS in the hoppers
  while (digitalRead(reedSw1) == HIGH) {  //Tab A10
    dispBbred();                          //Moves gate to side then returns to center [Tab A32]
    dispBbblue();                         //moves gate to other side then returns to center [Tab A32]
  }
}