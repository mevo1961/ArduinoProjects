//www.elegoo.com
//2016.06.13

int Led=13;//define LED port
int buttonpin=3; //define switch port
int val;//define digital variable val
int analogVal;
int sensorPin  =  A0;     // select the input  pin for  the potentiometer 
int ledPin  =  13;   // select the pin for  the LED
int sensorValue =  0;  // variable to  store  the value  coming  from  the sensor

void  setup()
{
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  pinMode(Led,OUTPUT);//define LED as a output port
  pinMode(buttonpin,INPUT);//define switch as a output port
  pinMode(sensorPin, INPUT);
}
void  loop()

{ 
  val=digitalRead(buttonpin);//read the value of the digital interface 3 assigned to val
  analogVal = analogRead(buttonpin);
  sensorValue =  analogRead(sensorPin);
  Serial.println(sensorValue,  DEC);
  Serial.println(analogVal, DEC);
   
  if(val==HIGH)//when the switch sensor have signal, LED blink
  {
    digitalWrite(Led,HIGH);
  }
  else
  {
    digitalWrite(Led,LOW);
  }
  delay(1000);
}

