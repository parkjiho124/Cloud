#include <DHT.h>
#include <ESP8266WiFi.h>
#define DHTPIN  D4  // D0
#define DHTTYPE DHT11

const char* ssid = "SK_WiFi0801";
const char* password = "1412022841";

const char* server = "api.thingspeak.com";
String apiKey = "FJDC22J89ERWQKZT"; // Write API Key

WiFiClient client;
DHT dht(DHTPIN, DHTTYPE, D4);

int blue_led = D2;

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(blue_led, OUTPUT);
  Serial.println();
  Serial.println("ThingSpeak");
  // DHT11 초기화
  dht.begin();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Wi-Fi 초기화
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!!");
}
void loop() {
  float t, h;
  t = dht.readTemperature();
  h = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read!!");
    digitalWrite(blue_led, LOW);
    delay(1000);
    return;
  }

  if (client.connect(server,80)) {// "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(t);
           postStr +="&field2=";
           postStr += String(h);
           postStr += "\r\n\r\n";
    digitalWrite(blue_led, HIGH);
    delay(1000);
  
    // Rest API POST 요청 : 웹서버에 resource 생성 요청
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");

    // 온도 데이터를 한번 전송하고 client와 연결을 끊고 15초 시간 지연 대기 한다.
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temp : ");
    Serial.print(t);
    Serial.print("\t Humidity: ");
    Serial.print(h);
    Serial.println("%. Send to Thingspeak.");
  }
  client.stop();

  Serial.println("Waiting...");
  // Thingspeak 무료 계정은 업데이트 주기가 15초임
  delay(15000);
}
