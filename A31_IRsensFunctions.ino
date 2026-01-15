/*This is the Code for reading IR Sensors of the IIOT at camosun innovates
To add more sensors or LEDs (things you want to trigger).  Add to the corresponding Array
and Matrix.

IR sensor is Sharp GP2Y0A51SK0F

A debounce or time delay may be needed to added to the readings as sometimes a 
rapid change in lighting or a round container can cause it to missfire/fire twice

Ask Luke if any questions you have*/

//All readings come for the irSensorM matrix
void readIR1() {  //Reads and updates distance of IR sensor 1
  irSensorM[0][0] = analogRead(irScontDisp) * 0.0048828125 * cal;
  irSensorM[0][1] = 13 * pow(irSensorM[0][0], -1);
}
void readIR2() {  //Reads and updates distance of IR sensor 2
  irSensorM[1][0] = analogRead(irScontready) * 0.0048828125 * cal;
  irSensorM[1][1] = 13 * pow(irSensorM[1][0], -1);
}
void readIR3() {  //Reads and updates distance of IR sensor 3
  irSensorM[2][0] = analogRead(irSbbfilltgt) * 0.0048828125 * cal;
  irSensorM[2][1] = 13 * pow(irSensorM[2][0], -1);
}

void readIR4() {  //Reads and updates distance of IR sensor 4
  irSensorM[3][0] = analogRead(irSlblqueuef1) * 0.0048828125 * cal;
  irSensorM[3][1] = 13 * pow(irSensorM[3][0], -1);
}

void readIR5() {  //Reads and updates distance of IR sensor 5
  irSensorM[4][0] = analogRead(irSlabeltgtf2) * 0.0048828125 * cal;
  irSensorM[4][1] = 13 * pow(irSensorM[4][0], -1);
}


//Pin Realocated
// void readIR6() {  //Reads and updates distance of IR sensor 6
//   irSensorM[5][0] = analogRead(peelLabel) * 0.0048828125 * cal;
//   irSensorM[5][1] = 13 * pow(irSensorM[2][0], -1);
// }

void readIRSensors() {  //Reads all the IR sensors and updates their varriables
  readIR1();
  readIR2();
  readIR3();
  readIR4();
  readIR5();
  //readIR6();
}

void printIR() {  //Prints the distance values of the IR sensors (Grabs from matrix) but does not update the IR sensors before doing so.
  //readIRSensors();
  for (int j = 0; j < y; j++) {
    Serial.print(irSensorM[j][1]);
    Serial.print(" cm ");
    Serial.print(irstatearray[j]);
    Serial.print(" , ");
  }
  Serial.println();
}

/*
Reads the sensors and triggers LED based on the reading.
Logic checks if the distance the IR is reading is greater tha distance
detect threshold and less than the upper distance detect threshold (Change threshold in the variable section)
*/
void irRefresh() {
  readIRSensors();
  for (int j = 0; j < y; j++) {
    if (irSensorM[j][1] > irSensorM[j][2] && irSensorM[j][1] < irSensorM[j][3]) {
      irstatearray[j] = true;
    } else {
      irstatearray[j] = false;
    }
    delay(7);
  }
  //printIR();
}

void checkIR() {  //Does a quick one time reading of the IR sensors and prints results
  irRefresh();
  printIR();
}

void sensorCalibration() {  //to calibrate the sensors to determine the min, max, and average distance for each one
  Serial.println("Starting Sensor Calibration, Please Wait....");
  for (int j = 0; j < y; j++) {  //The for loop runs through all the different IR sensors to find the new detection threshold for each individual one
    totalValue = 0;              //resets the total value to make sure each sensor is only avaraged by its self [Tab A20]
    numReadings = 0;             //resets the number of readings to make sure each sensor is only avaraged by its self [Tab A20]
    sensorReadingValue = 0;      //resets the sensor reading value (average) to make sure each sensor is only avaraged by its self [Tab A20]
    Serial.print("Calibrating IRSensor");
    Serial.println(j + 1);        //J+1 to make the sensors print the correct number suffix to each sensors
    readIRSensors();              //calls readITSensors function [Tab A31]
    calibrationStart = millis();  //Sets the calibration start time to the currente millis time so the sensors all get the same amount of read time
    irAVG[j] = irSensorM[j][1];   //updates the array for the sensor readings with the current detection threshold reading.  This is so that the min and max will update proberly this ensures reliablity with the reading values gathered.
    irMin[j] = irSensorM[j][1];   //updates the array for the sensor readings with the current detection threshold reading.  This is so that the min and max will update proberly this ensures reliablity with the reading values gathered.
    irMax[j] = irSensorM[j][1];   //updates the array for the sensor readings with the current detection threshold reading.  This is so that the min and max will update proberly this ensures reliablity with the reading values gathered.
    delay(10);  //small debounce 
    while (millis() - calibrationStart < calibrationDuration) {  //Only run the while for the set duration [Tab A20]
      checkIR();    //Update the sensors with current reading
      sensorReadingValue = irSensorM[j][1];   //Set the holding varible [Tab A20] to the current Sensor value
      if (sensorReadingValue < irMin[j]) {    //If the holding variable is less than current Sensor minimum value, update it to the new lowest
        irMin[j] = sensorReadingValue;
      }
      if (sensorReadingValue > irMax[j]) {  //If the holding variable is greater than current Sensor max value, update it to the new highest
        irMax[j] = sensorReadingValue;
      }
      totalValue += sensorReadingValue;   //Collect total value of all sensors readings
      numReadings++;    //count how may readings have been taken 
      //delay(50);
    }
    irAVG[j] = totalValue / numReadings;    //Calculate and update the average value of the readings taken for the Sensro
  }
  Serial.println("Calibration Routine Results:");
  for (int j = 0; j < y; j++) {  //Print the results of the calibration (Display the numbers collected);
    Serial.print("IRSensor");
    Serial.print(j + 1);
    Serial.print(": ");
    Serial.print("Average = ");
    Serial.print(irAVG[j]);
    Serial.print("cm");
    Serial.print(" ; ");
    Serial.print("Max = ");
    Serial.print(irMax[j]);
    Serial.print("cm");
    Serial.print(" ; ");
    Serial.print("Min = ");
    Serial.print(irMin[j]);
    Serial.println("cm");
  }
}

/*
Note:  it maybe be a good idea to add a confirmation check to the calibration update.  Like a serial input Y/N to makes sure the values that the new values are the ones you want.
maybe even displaying "Current value -> New value" side by side so you know what each will become
*/
void calibrationUpdate() {  //Function that updates all the detecton thresholds for all IR sensors
  Serial.println("updating detection threshold");
  for (int j = 0; j < y; j++) {  //The for loop prints off all the current sensor detection thresholds
    Serial.print("Current IRSensor");
    Serial.print(j + 1);  //j+1 is so that the written text to the Serial reads properly.  With out the plus one it will read IRSensor0 tahter than IRSensor1
    Serial.print(" = ");
    Serial.print(irSensorM[j][2]);  //The location in the matrix where the detection threshold values are held [Tab A20]
    Serial.println("cm");
  }
  for (int j = 0; j < y; j++) {
    irSensorM[j][2] = irMax[j] + 2;  //Changes the new detection threshold to the max value read during sensorCalibration [Tab A31] + 2 to give it a buffer for detection (i.e.  irMax1 = 14.5  -> new detection threshold is 16.5)
    Serial.print("New IRSensor");    //j+1 is so that the written text to the Serial reads properly.  With out the plus one it will read IRSensor0 tahter than IRSensor1
    Serial.print(j + 1);
    Serial.print(" = ");
    Serial.print(irSensorM[j][2]);  //Prints the new value that Detection threshold has been updated too
    Serial.println("cm");
  }
}
