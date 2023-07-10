#include <DHT.h>

DHT sensor(A1, DHT11);

const int dry = 600;
const int wet = 190;
const int dark = 1023;
const int illu = 0;

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  float temperature = sensor.readTemperature();
  float humAir = sensor.readHumidity();
  float humSoil = map(analogRead(A2), wet, dry, 100, 0);
  float bright = map(analogRead(A4), illu, dark, 100, 0);
  
  Serial.print(temperature);
  
  Serial.print(";");
  Serial.print(humAir);

  Serial.print(";");
  Serial.print(humSoil);

  Serial.print(";");
  Serial.println(bright);

  delay(1000);
}