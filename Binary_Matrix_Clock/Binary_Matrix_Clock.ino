#include "Arduino.h"
#include "LedControl.h"
#include "TimeLib.h"
#include "DS3232RTC.h"
#include "Wire.h"

LedControl lc=LedControl(12,10,11,1);


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

void setNumberToMatrixColumn(int column, int number, int intensity) {
	// print a number ranging from 0 - 59 into column and column + 1 of led matrix
	// each bit consists of a 2x2 array of LEDs
	// intensity must range from 0 .. 15
	byte firstDigit  = doubleBinaryNumber((byte)(number / 10));
	byte secondDigit = doubleBinaryNumber((byte)(number % 10));

	lc.setIntensity(0,intensity);
	lc.setColumn(0, 2 * column,     firstDigit);
	lc.setColumn(0, 2 * column + 1, firstDigit);
	lc.setColumn(0, 2 * column + 2, secondDigit);
	lc.setColumn(0, 2 * column + 3, secondDigit);
}

void setNumberToMatrixRow(int row, int number, int intensity) {
	// print a number ranging from 0 - 59 into row and row + 1 of led matrix
	// each bit consists of a 2x2 array of LEDs
	// intensity must range from 0 .. 15
	byte firstDigit  = doubleBinaryNumber((byte)(number / 10));
	byte secondDigit = doubleBinaryNumber((byte)(number % 10));

	lc.setIntensity(0,intensity);
	lc.setRow(0, 2 * row,     firstDigit);
	lc.setRow(0, 2 * row + 1, firstDigit);
	lc.setRow(0, 2 * row + 2, secondDigit);
	lc.setRow(0, 2 * row + 3, secondDigit);
}

//The setup function is called once at startup of the sketch
void setup()
{
	/*
	   The MAX72XX is in power-saving mode on startup,
	   we have to do a wakeup call
	 */
	lc.shutdown(0,false);
	// Set the brightness to a medium value
	lc.setIntensity(0,8);
	// and clear the display
	lc.clearDisplay(0);
	Serial.begin(9600);
	Serial.begin(9600);
	setSyncProvider(RTC.get);   // the function to get the time from the RTC
	if(timeStatus() != timeSet)
		Serial.println("Unable to sync with the RTC");
	else
		Serial.println("RTC has set the system time");
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	time_t t = now();
	int intensity = 4;
	setNumberToMatrixRow(0, hour(t), intensity);
	setNumberToMatrixRow(2, minute(t), intensity);
	Serial.println(hour(t));
	Serial.println(minute(t));
	Serial.println(second(t));
	delay(1000);
}


