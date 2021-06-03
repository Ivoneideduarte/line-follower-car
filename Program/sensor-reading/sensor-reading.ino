#define rightSensor 2
#define leftSensor 3

void setup() {
  Serial.begin(9600);
}

void loop() {
  bool statusRightSensor = digitalRead(rightSensor);
  bool statusLeftSensor = digitalRead(leftSensor);
  Serial.println("Right Sensor: " + String(statusRightSensor));
  Serial.println("Left Sensor: " + String(statusLeftSensor));
}
