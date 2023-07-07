#include <DHT.h>

DHT sensor(A1, DHT11);

const int dry = 400;
const int wet = 200;
const int dark = 1023;
const int illu = 100;

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  float temperature = sensor.readTemperature();
  float humAir = sensor.readHumidity();
  float humSoil = map(analogRead(A2), wet, dry, 100, 0);
  float gasConc = map(analogRead(A3), 1023, 0, 100, 0);
  float bright = map(analogRead(A4), illu, dark, 100, 0);
  
  Serial.print("TempC ");
  Serial.print(temperature);
  
  Serial.print(" HumiAir ");
  Serial.print(humAir);

  Serial.print(" HumiSoil ");
  Serial.print(humSoil);

  Serial.print(" Bright ");
  Serial.print(bright);

  Serial.print(" Gas ");
  Serial.println(gasConc);

  delay(2000);
}