//www.elegoo.com
//2016.12.9


// include the library code:
#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)
#include <SimpleDHT.h>

#define lcdColumns 16
#define lcdLines   2

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
int buzzer   = 4;
SimpleDHT11 dht11;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
long delayCounter = 0;
boolean alarmSet = false;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(lcdColumns, lcdLines);
  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output

  Serial.begin(9600);
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet) 
      Serial.println("Unable to sync with the RTC");
  else
      Serial.println("RTC has set the system time");

  digitalClockDisplay(0, 0);
  tempAndHumDisplay(0, 1, &alarmSet); 
}

void loop() {
  
  digitalClockDisplay(0, 0);
  if (delayCounter >= 6000)
  {
    // update temperature and humidity only once per minute
    tempAndHumDisplay(0, 1, &alarmSet);
    delayCounter = 0;
  } 
  delay(100);
  delayCounter +=100;
}

void digitalClockDisplay(int column, int line)
{
    // digital clock display of the time and date
    lcd.setCursor(column, line);
    printDigits(hour(), ':');
    printDigits(minute(), ':');
    printDigits(second(), ' ');
    lcd.setCursor(column + 10, line);
    printDigits(day(), '.');
    printDigits(month(), '.');
    // printDigits(year(), ' '); 
}

void tempAndHumDisplay(int column, int line, boolean *alarmSet)
// get temperature and humidity from DHT11 module
{
  // read DHT11 with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.print("Read DHT11 failed");
    return;
  }
  lcd.setCursor(column, line);
  printDigits(temperature, char(223));
  lcd.print("C");
  lcd.setCursor(lcdColumns - 3, line);
  printDigits(humidity, '%');
  if (humidity > 50)
  {
    giveAlarm(5, alarmSet);
  }
  else
  {
    *alarmSet = false;
  }
}

void printDigits(int digits, char separator)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    if(digits < 10)
        lcd.print('0');
    lcd.print(digits);
    lcd.print(separator);
}

void giveAlarm(int duration, boolean *alarmSet)
// duration defines the duration of the alarm in seconds
{
  
  if ( ! *alarmSet)
  {
    *alarmSet = true;
    for(int i = 0; i < duration * 500; i++)
    {
      digitalWrite(buzzer,HIGH);
      delay(1);//wait for 1ms
      digitalWrite(buzzer,LOW);
      delay(1);//wait for 1ms
    }
  }
}

