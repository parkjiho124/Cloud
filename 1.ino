#include <DHT.h>
#define DHTPIN D4
#define DHTTYPE DHT11
 
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  Serial.begin(115200);
  dht.begin();
}
 
void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("   Humi: ");
  Serial.println(humi);
  delay(1000);
}
