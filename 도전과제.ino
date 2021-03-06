#define yellow D0 // LED in NodeMCU at pin GPIO16 (D0).
#define blue D2
#define red D4

int count = 0;
bool direction = true;

void setup() {
pinMode(yellow, OUTPUT); // set the digital pin as output.
pinMode(blue, OUTPUT);
pinMode(red, OUTPUT);
}

 void blinkLED(int ledPin, int delayTime){
    digitalWrite(ledPin, HIGH);
    delay(delayTime);          
    digitalWrite(ledPin, LOW); 
    delay(delayTime);
    count++;   
  }
  
void loop() {
  count = 0;
  if(direction){
    blinkLED(yellow, 300);  //1
    blinkLED(blue, 300); //2
    blinkLED(red, 300); //3
    direction = false;  
  }
  if (!direction){
    blinkLED(blue, 300); //2
    blinkLED(yellow, 300); //1
    direction = true;
  } 
  if (direction){ 
     blinkLED(blue, 300); //2
     blinkLED(red, 300); //3
     direction = false;
  } else {
    blinkLED(blue, 300); //2
    direction = true;
  }
}