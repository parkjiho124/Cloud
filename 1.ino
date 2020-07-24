#include <ESP8266WiFi.h>
#include <FirebaseArduio.h>
#define DHTPIN D2
#define DHTTYPE DHT11
#include <DHT.h>

DHT dht(DHTPIN, DHTTYPE);

#define FIREBASE_HOST "mydhtsensor-6b684.firebaseio.com"
#define FIREBASE_AUTH "JPUmJOaFAOKvGZFqV3OTPb5WYO2MHmfwykQs7iFC"
#define WIFI_SSID "201912739"
#define WIFI_PASSWORD "jh010124"

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  dht.begin(9600);

  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Humidity = ");
  Serial.println(humi);

  Firebase.setFloat("temperature", temp);
  Firebase.setFloat("humidity", humi);

  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.println("sent data to firebase");
  delay(5000);
  }

}
