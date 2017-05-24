//www.elegoo.com
//2016.12.08

#include "SR04.h" //  https://github.com/mrRobot62/Arduino-ultrasonic-SR04-library
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
int buzzer = 4;//the pin of the active buzzer

void setup() {
   Serial.begin(9600);
   pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
   delay(1000); 
}

void loop() {
  a=sr04.Distance();
  Serial.print(a);
  Serial.println("cm");
  distanceAlarm(a);
  
  // delay(1);
}

void distanceAlarm(int dist)
{
  if (dist < 10)
  {
    beepQuick();
  }
  else if (dist < 25)
  {
    beepMiddle();  
  }
  else if (dist < 50)
  {
    beepSlow();
  }
}

void beepSlow(void)
{
  int i, j;
  for(j = 0; j < 100; j++)
  {
    digitalWrite(buzzer,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(1);//wait for 1ms
  }
  delay(200);
}

void beepMiddle(void)
{
  int i, j;
  for(j = 0; j < 50; j++)
  {
    digitalWrite(buzzer,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(1);//wait for 1ms
  }
  delay(100);
}

void beepQuick(void)
{
  int i, j;
  for(j = 0; j < 25; j++)
  {
    digitalWrite(buzzer,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(1);//wait for 1ms
  }
  delay(50);
}

