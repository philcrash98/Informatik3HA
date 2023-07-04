#include <DHT.h>

DHT sensor(2, DHT11);

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  float temperature = sensor.readTemperature();
  float temperatureF = sensor.convertCtoF(temperature);
  float humidity = sensor.readHumidity();
  
  Serial.print("Temperature (°C): ");
  Serial.println(temperature);
  
  Serial.print("Humidity (%RH): ");
  Serial.println(humidity);

  delay(5000);
}