//www.elegoo.com
//2016.12.12

#include "Stepper.h"
#include "IRremote.h"

/*----- Variables, Pins -----*/
#define STEPS  2048   // Number of steps per revolution of Internal shaft
long Speed = 12; // speed given in rpm
int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin 6

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

Stepper small_stepper(STEPS, 8, 10, 9, 11);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

void makeSteps(int numOfSteps)
{
	small_stepper.setSpeed(Speed); //Max seems to be 500
	small_stepper.step(numOfSteps);
}

void increaseSpeed(void)
{
	if (Speed < 18)
	{
		Speed++;
	}
	Serial.print("Current speed is: ");
	Serial.println(Speed);
}

void decreaseSpeed(void)
{
	if (Speed > 1)
	{
		Speed--;
	}
	Serial.print("Current speed is: ");
	Serial.println(Speed);
}

void setup()
{ 
  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);
  Serial.print("Current speed is: ");
  Serial.println(Speed);
}

void loop()
{
	if (irrecv.decode(&results)) // have we received an IR signal?

	{
		switch(results.value)

		{
		case 0xFFA857: // VOL- button pressed
			makeSteps(-2048);
			delay(500);
			break;

		case 0xFF629D: // VOL+ button pressed
			makeSteps(2048);
			delay(500);
			break;

		case 0xFFE01F: // Arrow down pressed
			decreaseSpeed();
			delay(500);
			break;

		case 0xFF906F: // Arrow up pressed
			increaseSpeed();
			delay(500);
			break;
		}

		irrecv.resume(); // receive the next value
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
		digitalWrite(10, LOW);
		digitalWrite(11, LOW);
	}


}/* --end main loop -- */
