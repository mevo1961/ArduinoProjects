//www.elegoo.com
//2016.12.9

int buzzer = 12; //the pin of the active buzzer
int pirPin = 7; // Input for HC-S501

int pirValue; // Place to store read PIR Value


void setup() 
{  
  pinMode(buzzer, OUTPUT);
  pinMode(pirPin, INPUT);
 
  digitalWrite(buzzer, LOW);
}

void loop() {
  pirValue = digitalRead(pirPin);
  digitalWrite(buzzer, pirValue);
}
