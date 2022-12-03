#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 7
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display



void setup() {
   
 sensors.begin();

 lcd.begin (16,2);  // initialize the lcd 
// Switch on the backlight
 lcd.backlight();
   lcd.clear();
  lcd.setCursor(0,0);
}

void loop() {
  tmElements_t tm;

  sensors.requestTemperatures(); // Send the command to get temperatures 
 // Serial.print("Temperature for the device 1 (index 0) is: ");
  float x=sensors.getTempCByIndex(0);
  
  if (RTC.read(tm)) {
    
    lcd.setCursor(0,0); //Start at character 0 on line 0
    lcd.print("TIME: ");
//  lcd.setCursor(6,0); 
    print2digits(tm.Hour);
    lcd.print(':');
    print2digits(tm.Minute);
    lcd.print(':');
    print2digits(tm.Second);
    
    lcd.setCursor(0,1); //Start at character 0 on line 1
    lcd.print("Temp:  "); 
    lcd.print(x);

   
  } 
  delay(990);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.print('0');
  }
  lcd.print(number);
}
