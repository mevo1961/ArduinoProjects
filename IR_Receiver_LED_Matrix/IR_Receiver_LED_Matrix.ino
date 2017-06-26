//www.elegoo.com
//2016.12.9

#include "IRremote.h"
#include "LedControl.h"

#define ACTION_DIGIT   100
#define ACTION_VOLUME  101
#define ACTION_UP_DOWN 102
#define ACTION_MOVE    103
#define ACTION_STOP    104
#define ACTION_EQ      105
#define ACTION_REPT    106
#define ACTION_POWER   107
#define ACTION_REPEAT  108
#define ACTION_PAUSE   109

int receiver    = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
int nextDigit   = 0;
int column      = 0;
int factor      = 2;
int intensity   = 8;
int nextAction  = 0;
int deltaVolume = 0;
int deltaMove   = 0;
int deltaUpDown = 0;



/*-----( Declare objects )-----*/
LedControl lc=LedControl(7,5,6,1);
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

	switch(results.value)

	{
		case 0xFFA25D: nextAction = ACTION_POWER;                      break;
		case 0xFFE21D: nextAction = ACTION_STOP;                       break;
		case 0xFFA857: nextAction = ACTION_VOLUME;  deltaVolume = -1;  break;
		case 0xFF629D: nextAction = ACTION_VOLUME;  deltaVolume =  1;  break;
		case 0xFF22DD: nextAction = ACTION_MOVE;    deltaMove   = -1;  break;
		case 0xFFC23D: nextAction = ACTION_MOVE;    deltaMove   =  1;  break;
		case 0xFF02FD: nextAction = ACTION_PAUSE;                      break;
		case 0xFFE01F: nextAction = ACTION_UP_DOWN; deltaUpDown = -1;  break;
		case 0xFF906F: nextAction = ACTION_UP_DOWN; deltaUpDown =  1;  break;
		case 0xFF9867: nextAction = ACTION_EQ;                         break;
		case 0xFFB04F: nextAction = ACTION_REPT;                       break;
		case 0xFF6897: nextAction = ACTION_DIGIT;   nextDigit    = 0;  break;
		case 0xFF30CF: nextAction = ACTION_DIGIT;   nextDigit    = 1;  break;
		case 0xFF18E7: nextAction = ACTION_DIGIT;   nextDigit    = 2;  break;
		case 0xFF7A85: nextAction = ACTION_DIGIT;   nextDigit    = 3;  break;
		case 0xFF10EF: nextAction = ACTION_DIGIT;   nextDigit    = 4;  break;
		case 0xFF38C7: nextAction = ACTION_DIGIT;   nextDigit    = 5;  break;
		case 0xFF5AA5: nextAction = ACTION_DIGIT;   nextDigit    = 6;  break;
		case 0xFF42BD: nextAction = ACTION_DIGIT;   nextDigit    = 7;  break;
		case 0xFF4AB5: nextAction = ACTION_DIGIT;   nextDigit    = 8;  break;
		case 0xFF52AD: nextAction = ACTION_DIGIT;   nextDigit    = 9;  break;
		case 0xFFFFFFFF:                                               break; // Repeat: leave nextAction unchanged

		default:
			Serial.println(" other button   ");						   break;

	}




} //END translateIR

void executeAction(int action)
{
	Serial.print("Next action is: ");
	Serial.println(action);
	switch (action)
	{
	case ACTION_DIGIT:   handleDigit(nextDigit);        break;
	case ACTION_UP_DOWN: handleIntensity(deltaUpDown);  break;
	case ACTION_STOP:    handleStop();                  break;

	default:                                            break; //leave all other buttons unattended for now
	}
}

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

void setDigitToMatrixColumn(int column, int digit, int factor, int intensity) {
	// print a number ranging from 0 - 59 into column and column + 1 of led matrix
	// each bit consists of a factor x factor array of LEDs
	// intensity must range from 0 .. 15
	byte largeDigit  = enlargeBinaryNumber((byte)(digit), factor);

	lc.setIntensity(0,intensity);
	for (int i=0; i < factor; i++) {
		lc.setColumn(0, factor * column + i, largeDigit);
	}
}

void wakeUpMatrix(void) {
	// The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
	lc.shutdown(0,false);
	// Set the brightness to a medium value
	lc.setIntensity(0,intensity);
	// and clear the display
	lc.clearDisplay(0);
}

void handleIntensity(int delta)
{
	intensity += delta;
	if (intensity > 15) {
		intensity = 15;
	}
	if (intensity < 0) {
		intensity = 0;
	}
	lc.setIntensity(0,intensity);
}

void handleDigit(int digit)
{
	if (column < (8 / factor)) {
		if (digit < 10) {
			setDigitToMatrixColumn(column++, digit, factor, intensity);
			Serial.println(digit);
		}
	}
}

void handleStop(void)
{
	nextDigit = 0;
	column = 0;
	lc.clearDisplay(0);
	nextAction = 0;
	deltaVolume = 0;
	deltaMove = 0;
	deltaUpDown = 0;
}


void setup()   /*----( SETUP: RUNS ONCE )----*/
{
	wakeUpMatrix();
	setDigitToMatrixColumn(0, 5, factor, intensity);
	Serial.begin(9600);
	Serial.println("IR Receiver Button Decode");
	irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{

	if (irrecv.decode(&results)) // have we received an IR signal?

	{

		translateIR();
		executeAction(nextAction);

		delay(500); // Do not get immediate repeat
		irrecv.resume(); // receive the next value
	}
}/* --(end main loop )-- */


