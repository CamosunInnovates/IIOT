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
  irSensorM[3][1] = 13 * pow(irSensorM[2][0], -1);
}

void readIR5() {  //Reads and updates distance of IR sensor 5
  irSensorM[4][0] = analogRead(irSlabeltgtf2) * 0.0048828125 * cal;
  irSensorM[4][1] = 13 * pow(irSensorM[2][0], -1);
}

void readIR6() {  //Reads and updates distance of IR sensor 6
  irSensorM[5][0] = analogRead(irSsysoutf3) * 0.0048828125 * cal;
  irSensorM[5][1] = 13 * pow(irSensorM[2][0], -1);
}

void readIRSensors() {  //Reads all the IR sensors and updates their varriables
  readIR1();
  readIR2();
  readIR3();
  readIR4();
  readIR5();
  readIR6();
}

void printIR() {  //Prints the distance values of the IR sensors (Grabs from matrix)
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
Logic checks if the distance the IR is reading is greater than the distance
than the detect threshold (Change threshold in the variable section)
*/
void irRefresh() {
  readIRSensors();
  for (int j = 0; j < y; j++) {
    if (irSensorM[j][1] > irSensorM[j][2]) {
      irstatearray[j] = true;
    } else {
      irstatearray[j] = false;
    }
  }
  //printIR();
}