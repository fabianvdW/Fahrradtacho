const float wheelSize = 2.174; // m
float distance = 0.0;
unsigned long lastTurnTime = 0;
unsigned long deltaTime = millis();

void callback() {
  deltaTime = millis() - lastTurnTime;
  lastTurnTime = millis();
  distance += wheelSize;
}

void setup() {
  Serial.begin(9600);
  Serial.println("BLE Test");

  pinMode(2, INPUT);

  attachInterrupt(digitalPinToInterrupt(2), callback, FALLING);
}

void loop() {
  float speed = wheelSize / deltaTime * 1000;
  Serial.print("speed=");
  Serial.print(speed * 3.6);
  Serial.println(" km/h");
  delay(100);
}
