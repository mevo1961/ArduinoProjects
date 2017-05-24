//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  Serial.begin(9600);
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet) 
      Serial.println("Unable to sync with the RTC");
  else
      Serial.println("RTC has set the system time");
}

void loop() {
  // set the cursor to column 0, line 0
  digitalClockDisplay(0, 0);
  temperatureDisplay(10, 0); 
  delay(200);
}

void digitalClockDisplay(int column, int line)
{
    // digital clock display of the time and date
    lcd.setCursor(column, line);
    int hr = hour();
    if (hr < 10)
      lcd.print(' ');
    lcd.print(hr);
    printDigits(minute());
    printDigits(second());
    lcd.setCursor(column, line + 1);
    lcd.print(day());
    lcd.print('.');
    lcd.print(month());
    lcd.print('.');
    lcd.print(year()); 
}


void temperatureDisplay(int column, int line)
{
  float c = RTC.temperature() / 4.;
  float f = c * 9. / 5. + 32.;
  lcd.setCursor(column, line);
  // print temperature with one decimal digit
  lcd.print(c, 1);
  lcd.print(char(223));
  lcd.print("C");
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    lcd.print(':');
    if(digits < 10)
        lcd.print('0');
    lcd.print(digits);
}
