//www.elegoo.com
//2016.12.9

/*
	Display the time retrieved from an RTC module on a liquid crystal display
 */

#include <Arduino.h>

// include the library code:
#include <LiquidCrystal.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <TimeLib.h>
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


void printDigits(char sep, int digits)
{
    // utility function for digital clock display: prints preceding separator and leading 0
	// '~' is used to specify no separator
	if (sep != '~')
        lcd.print(sep);
    if(digits < 10)
        lcd.print('0');
    lcd.print(digits);
}

void digitalClockDisplay(int column, int line)
{
    // digital clock display of the time and date
    lcd.setCursor(column, line);
    int hr = hour();
    printDigits('~', hr);
    printDigits(':', minute());
    printDigits(':', second());
    lcd.setCursor(column, line + 1);
    printDigits('~', day());
    printDigits('.', month());
    printDigits('.', year());
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
