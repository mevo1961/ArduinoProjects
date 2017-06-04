//www.elegoo.com
//2016.12.12

// define the LED digit patterns, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
//                74HC595 pin     Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7 
//                Mapping to      a,b,c,d,e,f,g of Seven-Segment LED
byte seven_seg_digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110   // = 9
                             };
 
// connect to the ST_CP of 74HC595 (pin 3,latch pin)
int latchPin = 3;
// connect to the SH_CP of 74HC595 (pin 4, clock pin)
int clockPin = 4;
// connect to the DS of 74HC595 (pin 2)
int dataPin = 2;
// adjust the Brightness of the 7 segment display
int brightnessPin = 5;
// trimpoti for adjusting brightness
int potiPin = 0;
int brightness = 0; // 0 means maximum brightness, 255 means lowest
 
void setup() {
  // Set latchPin, clockPin, dataPin as output
  pinMode(latchPin,       OUTPUT);
  pinMode(clockPin,       OUTPUT);
  pinMode(dataPin,        OUTPUT);
  pinMode(brightnessPin,  OUTPUT);
}
 
// display a number on the digital segment display
void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);

  // set brightness to full
  analogWrite(brightnessPin, 0);
}
 
void loop() {       
  for (byte digit = 0; digit < 10; digit++) {
    sevenSegWrite(digit);
    for (int i = 0; i < 10; i++) {
      // get the value from poti and adjust brightness accordingly
      // poti values range from 0 to 1023, must be adjusted to 0 to 255
      brightness = analogRead(potiPin);
      analogWrite(brightnessPin, brightness / 4);
      delay(100);
    }
  }
   
  // now vary brightness of current digit from full to minimum
  delay(1000);
  for (int brightness = 5; brightness < 256; brightness+= 5) {
    analogWrite(brightnessPin, brightness);
    delay(50);
  }
  delay(1000);
}
