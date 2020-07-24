#include <ESP8266WiFi.h>
// 와이파이 공유기의 SSID
const char* ssid = "SK_WiFi0801"; 
// 와이파이 공유기의 접속 비밀번호         
const char* password = "1412022841"; 

int ledPin = D4;
int ledPin2 = D2;          // GPIO2 or D4
WiFiServer server(80);   // 웹서버용 포트 번호

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(ledPin, OUTPUT);    
  digitalWrite(ledPin, LOW);
  delay(100);
  pinMode(ledPin2, OUTPUT);    
  digitalWrite(ledPin2, LOW);

  // 와이파이 네트워크에 접속
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!!");

  // 웹서버 개시
  server.begin();
  Serial.println("Server started");

  // 접속할 IP 주소 표시
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.println("");
}

void loop() {
// 클라이언트가 접속되었는지 확인
  WiFiClient client = server.available();   
  if(!client) {  
    return;
  } 

  // 클라이언트가 데이터를 보낼 때까지 기다림
  Serial.println("new client");
  while(!client.available()) {
    delay(1);
  }

  // request의 첫번째 줄을 읽어들임 : GET / HTTP/1.1
  String request = client.readStringUntil('\r');
  Serial.print("request : ");
  Serial.println(request);
  client.flush();

  // request에 따른 LED 제어
  // request.indexOf는 "/LED=ON" 혹은 "/LED=OFF" 문자열이 있는지 찾고
  // 찾는 문자열이 있으면 문자열을 return하고, 없으면 -1을 return 한다.
  int value = LOW;
  if(request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;   
  }
  if(request.indexOf("/LED=OFF") != -1) {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

  
  if(request.indexOf("LED2=ON") != -1) {
    digitalWrite(ledPin2, HIGH);
    value = HIGH;   
  }
  if(request.indexOf("LED2=OFF") != -1) {
    digitalWrite(ledPin2, LOW);
    value = LOW;
  }

  // 클라이언트 request에 대한 응답 메시지
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("LED is turned ");
  
  if(value)
    client.print("On");
  else 
    client.print("Off");
  
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Yellow Turn On</button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Yellow Turn Off</button></a>");
  client.println("<br><br>");
  
  client.println("<a href=\"LED2=ON\"\"><button>Blue Turn On</button></a>");
  client.println("<a href=\"LED2=OFF\"\"><button>Blue Turn Off</button></a>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected!!");
  Serial.println();
}
