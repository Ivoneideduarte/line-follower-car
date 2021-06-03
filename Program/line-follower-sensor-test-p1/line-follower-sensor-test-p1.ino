//Sensors
#define rightSensor A0
#define leftSensor A1
bool statusRightSensor, statusLeftSensor;

//Engines
#define pinENA 3
#define pinN1 4
#define pinN2 5
#define pinENB 6
#define pinN3 7
#define pinN4 8

#define velRight 130
#define velLeft 130

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
  printValue();
}

void readSensor() {
  //line black - read sensor 1
  //floor white - read sensor 0
  statusRightSensor = digitalRead(rightSensor);
  statusLeftSensor = digitalRead(leftSensor);
}

void lineFollower() {
  //directionCar(ENA, N1, N2, N3, N4, ENB);
  //sensorRight = 0 and sensorLeft = 0 : forward
  if (!statusRightSensor and !statusLeftSensor) {
    directionCar(velRight, 1, 0, 1, 0, velLeft);
  }

  //sensorRight = 1 and sensorLeft = 1 : stop
  else if (statusRightSensor and statusLeftSensor) {
    directionCar(velRight, 0, 0, 0, 0, velLeft);
  }

  //sensorRight = 0 and sensorLeft = 1 : left
  else if (!statusRightSensor and statusLeftSensor) {
    directionCar(velRight, 0, 1, 1, 0, velLeft);
  }

  //sensorRight = 1 and sensorLeft = 0 : right
  else if (statusRightSensor and !statusLeftSensor) {
    directionCar(velRight, 1, 0, 0, 1, velLeft);
  }
}

void printValue() {
  Serial.println("Right Sensor: " + String(statusRightSensor));
  Serial.println("Left Sensor: " + String(statusLeftSensor));
}

void directionCar(byte ENA, bool N1, bool N2, bool N3, bool N4, byte ENB) {
  //Left Engine
  analogWrite(pinENA, ENA);
  digitalWrite(pinN1, N1);
  digitalWrite(pinN2, N2);
  //Right Engine
  digitalWrite(pinN3, N3);
  digitalWrite(pinN4, N4);
  analogWrite(pinENB, ENB);
}
