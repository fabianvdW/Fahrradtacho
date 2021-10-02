// MAC Address: E5AD7E6164E0

const float wheelSize = 2.174; // m
const float minSpeed = 2.; // km/h

float distance = 0.0; // m
unsigned long lastTurnTime = 0; // ms
unsigned long deltaTime = 1 << 15; // ms


float v(long delta){
  return wheelSize / delta * 1000 * 3.6;
}

void callback() {
  Serial.println("Umdrehung");
  long t = millis();
  deltaTime = t - lastTurnTime;
  lastTurnTime = t;
  distance += wheelSize;
}

void setup() {
  Serial.begin(9600);
  Serial.println("BLE Test");

  pinMode(2, INPUT);

  attachInterrupt(digitalPinToInterrupt(2), callback, FALLING);
}

void loop() {
  float speed = min(v(deltaTime), v(millis() - lastTurnTime));
  if(speed <= minSpeed){
    speed = 0.;
  }
  Serial.print("speed=");
  Serial.print(speed);
  Serial.println(" km/h");
  delay(500);
}
