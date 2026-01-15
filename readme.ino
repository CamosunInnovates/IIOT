/* 
This is the code for the V2 version of the IIOT Demonstration Porject for Camosun Innovates.
This current iteration uses Nextion Enhanced NX8048P070-011R - Generic 7.0" HMI 800*480 Touch Display for the HMI.
Along with an Arduino Mega as the control unit.

The Nextion has its own code editor and processing chip.  This is completly seperate from the arduino and is programmed independently with its own code style and system.
The arduino and HMI can pass information back and forth via serial communication.

Librarys:
"EasyNextionLibrary.h" (1.0.6) by Athanasios Seitanis - Accessed Sept 20, 2025

Code was written in colaboration by Jesus PL and Luke R at Camosun Innovates.

Updates:

September 15th, 2025
MAIN IIOT DEMO Program Created by JPL
Sensors and gate code was created by LR

Sept 25, 2025
LR and JPL integrated code and created a working set up for Camosun Innovates
open house

Sept 29, 2025
LR Went through and commented the code. (To be reviewd by JPL)

Oct 6, 2025
JPL reviewed comments and approved.

Oct 28, 2025
LR added primingPneumatics [Tab A30] was added

Nov 4, 2025
LR updated the save revision to V1.3 so that a working state of V1.2 will be preserved.
LR modifying dispensing to account for a first container to travel through straight to the material dispenser.  As well integrating dispensing to be based on sensors rather than timers.
A test program was created called Dispensing_WIP on Nov 3, 2025 by LR.  This logical step and flow chart that was used to created it is what the integration is being based on.

Created functions [Tab A30]
 - containerDispensing()
 - firstContainer()
 - nextContainer()
 - errorState()

Nov 5, 2025
LR created functions [Tab A30]
 - materialDispensing()
 - sendToMaterial()
 - lockRoutine()

Modified executeOrder() to distribute it to call other functions for easier reading and trouble shooting as well as added serial monitor prints to inform of errors
Replaced feedToTgt() with sendToMaterial()

Nov 6, 2025
Upreved to V1.4 - to account for many changes and stable version
 - JD from Camosun Innovates witnessed it working great in action

Nov 14, 2025
Added Tab A33
Created functions [Tab A33]
 - applyLabel()
 - labelHandeling()

Nov 19, 2025
Added Tabs: A34 & A35
moved relavent functions to each Tab
comments will be updated as they are found.  some tab comments may be out of date.  please update them as you catch them
adding/adjusting Serial communication and error catching functions to improve reliability
 - checkIR() [Tab A31]
 - serialWait() [Tab A30]


Nov 20, 2025
added:
 - State Check() [Tab A30]

 more Serial Error Checks

Nov 24, 2025
Updated to 1.5 Unstable

Dec 2, 2025
Created function
 - labelDispensing()

Dec 8, 2025
Changed Gate delay value to reflext the new physical flow control valves added to the system
redGateTimer:900 -> New Value       
blueGateTimer:1100 -> New Value

Dec 10, 2025
LabelCase() function to handle labeler was implemented
 - lastContainertoLabel()  [Tab A33]

Dec 22, 2025
 - Comments all up to date
 - the transiting of containers is the only logic that isn't working.  Goal is to run things in parrallel best one can with a Serial processor
 - Flow chart was created that should act as the guide to fix all the things wrong with moving of containers.

LR work term is done and will be handing off the duties to the next person.

Latest code base is V1.5_Unstable_D


/////////////////////////////////////////////////////////////
Screen communicaions happen through Serial1 on Pins 18 and 19.
Those are auto initialized when the Nexion1.begin() is called.
Remember to wire TX(Arduino[Mega]) to RX(Nextion[HMI])  and RX(mega) to TX(HMI)

KEYWORDS/Logic

-----MAIN BASIC FUNCTIONS-----
conveyorStop()
conveyorStart()

checkOrder()

greenLEDoff()
greenLEDon()
redLEDoff()
redLEDon()
redLEDslowFlash(numBlinks)
redLEDfastFlash(numBlinks)
greenLEDslowFlash(numBlinks)
greenLEDfastFlash(numBlinks)

dispContsq()
dispContcirc()
feedtoTgt()

dispBbred()
dispBbblue()
gateCentering()

applyLabel()


-----IRSENS SECTION-----
printIR()

irRefresh()

readIRSensors()
readIR1()
readIR2()
readIR3()
readIR4()
readIR5()
readIR6()

PINOUT
PLEASE REFER TO A10_Pins.ino tab for more information.

LOGIC






*/
