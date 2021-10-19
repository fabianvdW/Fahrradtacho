// MAC Address: E5AD7E6164E0
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

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
  // Init display
  display.begin();
  display.setContrast(60);
  display.setTextSize(2);
  display.clearDisplay();

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
  display.clearDisplay();
  display.println(int(speed * 100) / 100.); // Crazy rounding
  display.print("km/h");
  display.display();
  delay(500);
}
