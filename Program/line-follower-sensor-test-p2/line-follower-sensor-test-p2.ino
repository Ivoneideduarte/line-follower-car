//Sensors
#define rightSensor 3
#define leftSensor 2
bool statusRightSensor, statusLeftSensor;

//Engines
#define pinENA 5
#define pinN1 11
#define pinN2 6
#define pinN3 7
#define pinN4 8
#define pinENB 9

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

void readSensor() {
  //line black - read sensor 1
  //floor white - read sensor 0
  statusRightSensor = digitalRead(rightSensor);
  statusLeftSensor = digitalRead(leftSensor);
  //printValue("sensor");
}

void lineFollower() {
  //directionCar(ENA, N1, N2, N3, N4, ENB);
  //sensorRight = 0 and sensorLeft = 0 : forward
  if (!statusRightSensor and !statusLeftSensor) {
    directionCar(100, 1, 0, 1, 0, 80);
    //printValue("forward");
  }

  //sensorRight = 1 and sensorLeft = 1 : stop
  else if (statusRightSensor and statusLeftSensor) {
    directionCar(0, 0, 0, 0, 0, 0);
    //printValue("stop");
  }

  //sensorRight = 0 and sensorLeft = 1 : left
  else if (!statusRightSensor and statusLeftSensor) {
    directionCar(100, 1, 1, 1, 0, 80);
    //printValue("left");
  }

  //sensorRight = 1 and sensorLeft = 0 : right
  else if (statusRightSensor and !statusLeftSensor) {
    directionCar(100, 1, 0, 1, 1, 80);//motor direito motor esquerdo
    //printValue("right");
  }
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
  //printValue("direction");
}

void printValue(String comand) {
  Serial.println(comand);
  if (comand == "sensor") {
    Serial.println("Right Sensor: " + String(statusRightSensor));
    Serial.println("Left Sensor: " + String(statusLeftSensor));
  }
}
