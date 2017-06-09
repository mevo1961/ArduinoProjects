#include "Arduino.h"
#include "LedControl.h"
#include "TimeLib.h"
#include "DS3232RTC.h"

LedControl lc=LedControl(12,10,11,1);


byte enlargeBinaryNumber(byte number, int factor) {
	// double each bit of the given number
	// factor must be 1 or 2
	// if factor = 2, only the 4 LSBs of number are used
	if (factor < 1) {
		factor = 1;
	}
	if (factor > 2) {
		factor = 2;
	}
	byte result = (byte) number;
	if (factor == 2) {
		number &= B00001111; // we only use the 4 LSBs of given number
		byte pattern = B00000001;
		result  = B00000000;
		for (int i = 0; i < 4; i++) {
			byte temp = number & pattern;
			result = result >> 2;
			if (temp == B00000001) {
				result |= B11000000;
			}
			number = number >> 1;
		}
	}

	return result;
}

void setNumberToMatrixColumn(int column, int number, int factor, int intensity) {
	// print a number ranging from 0 - 59 into column and column + 1 of led matrix
	// each bit consists of a 2x2 array of LEDs
	// intensity must range from 0 .. 15
	byte firstDigit  = enlargeBinaryNumber((byte)(number / 10), factor);
	byte secondDigit = enlargeBinaryNumber((byte)(number % 10), factor);

	lc.setIntensity(0,intensity);
	for (int i=0; i < factor; i++) {
		lc.setColumn(0, factor * column + i, firstDigit);
	}
	for (int i=0; i < factor; i++) {
		lc.setColumn(0, factor * column + factor + i, secondDigit);
	}
}

void setNumberToMatrixRow(int row, int number, int factor, int intensity) {
	// print a number ranging from 0 - 59 into row and row + 1 of led matrix
	// each bit consists of a 2x2 array of LEDs
	// intensity must range from 0 .. 15
	byte firstDigit  = enlargeBinaryNumber((byte)(number / 10), factor);
	byte secondDigit = enlargeBinaryNumber((byte)(number % 10), factor);

	lc.setIntensity(0,intensity);
	for (int i=0; i < factor; i++) {
		lc.setRow(0, factor * row + i, firstDigit);
	}
	for (int i=0; i < factor; i++) {
		lc.setRow(0, factor * row + factor + i, secondDigit);
	}
}

void wakeUpMatrix(void) {
	// The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
	lc.shutdown(0,false);
	// Set the brightness to a medium value
	lc.setIntensity(0,8);
	// and clear the display
	lc.clearDisplay(0);
}

//The setup function is called once at startup of the sketch
void setup()
{
	wakeUpMatrix();
	setSyncProvider(RTC.get);   // the function to get the time from the RTC
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	time_t t = now();
	int intensity = 4;
	setNumberToMatrixRow(0, hour(t), 2, intensity);
	setNumberToMatrixRow(2, minute(t), 2, intensity);
	delay(250);
}


