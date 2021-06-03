/*
 * Project: Line follower car
 * Author: Ivoneide Duarte
 * IDE Arduino: v1.8.13
 * Data: Junho de 2021 
*/

//Sensors
#define rightSensorInt A0
#define rightSensorExt A2
#define leftSensorInt A1
#define leftSensorExt A3
int statusRightSensorInt, statusRightSensorExt, statusLeftSensorInt, statusLeftSensorExt;

#define forwardSpeed 95
#define returnIntSpeed 115
#define returnExtSpeed 120

bool white = 0, black = 1;

//Engines
#define pinENA 3
#define pinN1 4
#define pinN2 5
#define pinENB 6
#define pinN3 7
#define pinN4 8

void setup() {
  Serial.begin(9600);
  pinMode(pinENB, OUTPUT);
  pinMode(pinN1, OUTPUT);
  pinMode(pinN2, OUTPUT);
  pinMode(pinN3, OUTPUT);
  pinMode(pinN4, OUTPUT);
  pinMode(pinENA, OUTPUT);
}

void loop() {
  readSensor();
  lineFollower();
}

void readSensor()
{
  // White line - reading 0
  // Black line - reading 1
  statusRightSensorInt = digitalRead(rightSensorInt);
  statusLeftSensorInt = digitalRead(leftSensorInt);
  statusRightSensorExt = digitalRead(rightSensorExt);
  statusLeftSensorExt = digitalRead(leftSensorExt);
  printValue("sensor");
}

void lineFollower()
{
  /*
    White line - reading 0
    Black line - reading 1
    
    LeftSensorExt   LeftSensorInt   SensorInt  RightSensorExt  =  EnginerLeft   EngineRight
          0               0              0           0                 1            1         Stop
          1               1              1           1                 0            0         Forward 
          0               0              1           0                 1            0         Right 
          0               0              0           1                 1           -1         Right 
          0               1              0           0                 0            1         Left 
          1               0              0           0                -1            1         Left           
  */
  
  //LeftSensorExt = 1 and LeftSensorInt = 1 and RightSensorInt = 1 and RightSensorExt = 1: Stop
  if ((statusLeftSensorExt) and (statusLeftSensorInt) and (statusRightSensorInt) and (statusRightSensorExt)) {
    directionCar(0, 0, 0, 0, 0, 0); // ENA, N1, N2, N3, N4, ENB
    //printValue("stop");
  }

  //LeftSensorExt = 0 and LeftSensorInt = 0 and RightSensorInt = 0 and RightSensorExt = 0: Forward
  else if ((!statusLeftSensorExt) and (!statusLeftSensorInt) and (!statusRightSensorInt) and (!statusRightSensorExt)) {
    directionCar(forwardSpeed, 1, 0, 1, 0, forwardSpeed); // ENA, N1, N2, N3, N4, ENB
    //printValue("forward");
  }

  //LeftSensorExt = 0 and LeftSensorInt = 1 and RightSensorInt = 0 and RightSensorExt = 0: Left
  else if ((!statusLeftSensorExt) and (statusLeftSensorInt) and (!statusRightSensorInt) and (!statusRightSensorExt)) {
    directionCar(0, 1, 1, 1, 0, returnIntSpeed); // ENA, N1, N2, N3, N4, ENB
    //printValue("left");
  }
  
  //LeftSensorExt = 1 and LeftSensorInt = 0 and RightSensorInt = 0 and RightSensorExt = 0: Left
  else if ((statusLeftSensorExt) and (!statusLeftSensorInt) and (!statusRightSensorInt) and (!statusRightSensorExt)) {
    directionCar(returnExtSpeed, 0, 1, 1, 0, returnExtSpeed); // ENA, N1, N2, N3, N4, ENB
    //printValue("left inverse");
  }

  //LeftSensorExt = 0 and LeftSensorInt = 0 and RightSensorInt = 1 and RightSensorExt = 0: Right
  else if ((!statusLeftSensorExt) and (!statusLeftSensorInt) and (statusRightSensorInt) and (!statusRightSensorExt)) {
    directionCar(returnIntSpeed, 1, 0, 1, 1, 0); // ENA, N1, N2, N3, N4, ENB
    //printValue("right");
  }
  //LeftSensorExt = 0 and LeftSensorInt = 0 and RightSensorInt = 0 and RightSensorExt = 1: Right
  else if ((!statusLeftSensorExt) and (!statusLeftSensorInt) and (!statusRightSensorInt) and (statusRightSensorExt)) {
    directionCar(returnExtSpeed, 1, 0, 0, 1 , returnExtSpeed); // ENA, N1, N2, N3, N4, ENB
    //printValue("right inverse");
  }
}

void directionCar(byte ENA, bool N1, bool N2, bool N3, bool N4, byte ENB)
{
  //Left Engine
  analogWrite(pinENA, ENA);
  digitalWrite(pinN1, N1);
  digitalWrite(pinN2, N2);
  //Right Engine
  digitalWrite(pinN3, N3);
  digitalWrite(pinN4, N4);
  analogWrite(pinENB, ENB);
  //printValue("direction");
}

void printValue(String comand)
{
  Serial.println(comand);
  if (comand == "sensor") 
  {
    Serial.println("Right Sensor External: " + String(statusRightSensorExt));
    Serial.println("Right Sensor Internal: " + String(statusRightSensorInt));
    Serial.println("Left Sensor Internal: " + String(statusLeftSensorInt));
    Serial.println("Left Sensor External: " + String(statusLeftSensorExt));
  }

}
