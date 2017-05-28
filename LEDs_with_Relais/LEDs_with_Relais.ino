#include "Arduino.h"

#define SWITCH 7
#define JUICE  3
#define delayTime 20
//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(SWITCH, OUTPUT);
	pinMode(JUICE, OUTPUT);
	digitalWrite(SWITCH, HIGH);
	analogWrite(JUICE, 0);
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{
	int i =  0;
	// one LED on, from 0 to full
	digitalWrite(SWITCH, HIGH);
	analogWrite(JUICE, 0);

	for (i = 0; i < 256; i++)
	{
		analogWrite(JUICE, i);
		delay(delayTime);
	}
	// now switch to other LED and fade it
	digitalWrite(SWITCH, LOW);
	for (i = 255; i >= 0; i--)
	{
		analogWrite(JUICE, i);
		delay(delayTime);
	}
}
