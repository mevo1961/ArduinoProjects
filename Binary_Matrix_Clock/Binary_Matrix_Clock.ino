#include "Arduino.h"
#include "LedControl.h"
#include "TimeLib.h"

// TODO: the pins of the following command must be adapted!
LedControl lc=LedControl(12,10,11,1);

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
}

byte doubleBinaryNumber(byte number) {
	// double each bit of the given number
	number &= B00001111; // we only use the 4 LSBs of given number
	byte pattern = B00000001;
	byte result  = B00000000;
	for (int i = 0; i < 4; i++) {
		byte temp = number & pattern;
		result = result >> 2;
		if (temp == B00000001) {
			result |= B11000000;
		}
		number = number >> 1;
	}

	return result;
}


void setNumberToMatrix(int row, int number) {
	// print a number ranging from 0 - 59 into row and row + 1 of led matrix
	// each bit consists of a 2x2 array of LEDs
	byte firstDigit  = doubleBinaryNumber((byte)(number / 10));
	byte secondDigit = doubleBinaryNumber((byte)(number % 10));

	lc.setRow(0, row, firstDigit);
	lc.setRow(0, row + 1, secondDigit);
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	time_t t = now();
	setNumberToMatrix(0, hour(t));
	setNumberToMatrix(2, minute(t));
	delay(1000);
}


