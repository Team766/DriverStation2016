#include "UnoJoy.h"

/*
*not real values
*/

//buttons
int button1 = 2;
int button2 = 3;
int button3 = 1;
int button4 = 0;
int button5 = 4;
int button6 = 7;
int button7 = 5;
int button8 = 8;
int button9 = 10;
int button10 = 11;
int button11 = 6;
int button12 = 9;
int button13 = 12;


//catauplt
int fire = 5; 

//intital raise/fold arm (2 position switch)
int armUp = A1;
//preset arm position buttons
int arm1 = A2; //highest-tower
int arm2 = 2; //drawbridge
int arm3 = 3; //sally port
int arm4 = 4; //pick up 
//move arm up/down (Analog!)
int armMove = 4; //x

//to scale tower
int winch = 7;

//intake wheels rotations (3 position switch)
int wheelsSpinOut = 12;
int wheelsSpinIn = 13;

//preset heights
int intake1 = 8; //grab
int intake2 = 9; //up
int intake3 = 11; //down
int intake4 = 10; //store
//move intake up/down (Analog!)
int intakeMove = 5; //y

int light = 6;
int catapultBowlAngle = A3;

int sensorValueArm = 0;
int sensorValueIntake = 0;

void setup() {

  pinMode(fire, INPUT_PULLUP);

  pinMode(armUp, INPUT_PULLUP);
  pinMode(arm1, INPUT_PULLUP);
  pinMode(arm2, INPUT_PULLUP);
  pinMode(arm3, INPUT_PULLUP);
  pinMode(arm4, INPUT_PULLUP);
  pinMode(armMove, INPUT_PULLUP);
  
  pinMode(winch, INPUT_PULLUP);

  pinMode(wheelsSpinOut, INPUT_PULLUP);
  pinMode(wheelsSpinIn, INPUT_PULLUP);
  
  pinMode(intake1, INPUT_PULLUP);
  pinMode(intake2, INPUT_PULLUP);
  pinMode(intake3, INPUT_PULLUP);
  pinMode(intake4, INPUT_PULLUP);
  pinMode(intakeMove, INPUT_PULLUP);

  pinMode(light, INPUT_PULLUP);
  pinMode(catapultBowlAngle, INPUT_PULLUP);

  setupUnoJoy();
  
}


void loop() {
  //Megajoy setup stuff, calls controller setup method
  dataForController_t controllerData = getControllerData();
  //controllerData.buttonArray[2] |= (HIGH << 7);
  setControllerData(controllerData);
}

dataForController_t getControllerData(void) {

  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins

  //sets directinput pins to current OI button outputs

  controllerData.buttonArray = (!digitalRead(arm2) << button1);
  controllerData.buttonArray |= (!digitalRead(arm3) << button2);
  controllerData.buttonArray |= (!digitalRead(arm4) << button3);
  controllerData.buttonArray |= (!digitalRead(fire) << button4);
  controllerData.buttonArray |= (!digitalRead(light) << button5);
  controllerData.buttonArray |= (!digitalRead(winch) << button6);
  controllerData.buttonArray |= (!digitalRead(intake1) << button7);
  controllerData.buttonArray |= (!digitalRead(intake2) << button8);
  controllerData.buttonArray |= (!digitalRead(intake3) << button9);
  controllerData.buttonArray |= (!digitalRead(intake4) << button10); 
  controllerData.buttonArray |= (!digitalRead(wheelsSpinOut) << button11); 
  controllerData.buttonArray |= (!digitalRead(wheelsSpinIn) << button12);
  controllerData.buttonArray |= (!digitalRead(armUp) << button13);
  controllerData.buttonArray |= (!digitalRead(arm1) << 13);
  controllerData.buttonArray |= (!digitalRead(catapultBowlAngle) << 14);



  /*
  // Test here, the UnoJoy interface will not work
   // with this enabled
   for (int i = 2; i <= 10; i++){
   if(!digitalRead(i)){
   Serial.println("on:");
   Serial.print(i);
   }
   //    digitalWrite(i, HIGH);
   }*/


  //For 2015 we only have 1 analog axis, which
  //is the slider

  //sets sensorValue var to position of slider
  sensorValueArm = analogRead(armMove);
  sensorValueIntake = analogRead(intakeMove);

  //Sets analog axis equal to slider value
  //Megajoy looks for an 8 bit analog value but the analogRead() function returns a 10 bit value
  //Mapping sensorValue to a range of 0-255 will ensure an 8 bit value is returned
  controllerData.analogAxisArray[0] = map(sensorValueArm, 0, 1023, 0, 255);
  controllerData.analogAxisArray[1] = map(sensorValueIntake, 0, 1023, 0, 255);


  // And return the data!
  return controllerData;

}


//copy of Arduino map function that will return a float instead of an int
float mapAsFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
