void loop() {
  myNex.NextionListen();                            //A function for easyNextion Library that allows for the Arduino to receive serial commands from the Nextion HMI
  irRefresh();                                      //Updates Ir Sensors
  if (Nexion1.available() || Serial.available()) {  //Checks if their is a command from either the arduino serial terminal or HMI
    if (Nexion1.available()) {                      //checks If the HMI sent a command or information
      casevar = Nexion1.parseInt();                 // Read the serial information from the HMI and move to the appropriate case
      Serial.println(casevar);                      //Prints the case # that it will activate
    } else {
      casevar = Serial.parseInt();  //Commands to switch cases can be handed from the IDE Serial Terminal this is largely used for troublehooting and testing
      Serial.println(casevar);      //Prints the case # that it will activate
    }

    switch (casevar) {  //Reads the variable casevar to determine which case it should procede too.

      case 1:
        conveyorStart();  //Function that starts the conveyors to start moving [Tab A30]
        greenLEDon();     //calls function that turns HMI box LED on [Tab A30]
        redLEDon();       //calls function that turns HMI box LED on [Tab A30]
        break;
      case 2:
        conveyorStop();  //calls function to trun the system conveyors off [Tab 30]
        greenLEDoff();   //calls function that turns HMI box LED off [Tab A30]
        redLEDoff();     //calls function that turns HMI box LED off [Tab A30]
        break;
      case 3:
        dispContsq();  //calls function that dispenses a square container onto the conveyor [Tab A30]
        break;
      case 4:
        dispContcirc();  //calls function that dispenses a cicrle container onto the conveyor [Tab A30]
        break;
      case 5:
        checkOrder();  //calls a function that reads the HMI to determine what [Tab A30]
        executeOrder();
        break;
      case 6:
        gateCentering();  //DO NOT CALL IF THERE IS MATERIAL IN THE HOPPERS! a small function to send the gate back to neutral.  [Tab A32]
        break;
      case 7:
        feedtoLabler();  //Calls function that sends filled containers to the next module (Labeler) [Tab A30]
        break;
      case 8:
        systemsCheck();  //Turn on and off all relays in the system [Tab A30]
        break;
      case 9:
        primePneumatics();  //Call to Activate to indivdually fire all the pneumatics and relays to test the system and get air in all the lines [Tab A30]
        break;

      default:
        Serial.println("Default state");  //Deafulat state where nothing is active
        break;
    }
  }
}