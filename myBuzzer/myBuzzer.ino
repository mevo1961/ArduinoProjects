//www.elegoo.com
//2016.12.08

int buzzer = 4;//the pin of the active buzzer
void setup()
{
 pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
 giveAlarm(5);
}
void loop()
{
 
} 


void giveAlarm(int duration)
// duration defines the duration of the alarm in seconds
{
  int i;
  for(i = 0; i < duration * 500; i++)
   {
    digitalWrite(buzzer,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(1);//wait for 1ms
   }
}
