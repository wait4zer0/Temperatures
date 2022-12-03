#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
// Data wire is plugged into port 7 on the Arduino
#define ONE_WIRE_BUS 7
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
void setup(void)
{
  // start serial port
//  Serial.begin(9600);
//  Serial.println("Dallas Temperature IC Control Library Demo");
  // Start up the library
  sensors.begin();
   lcd.begin(16,2);
    lcd.backlight(); 
  lcd.clear();
  lcd.setCursor(0,0);
}
void loop(void)
{
  sensors.requestTemperatures(); // Send the command to get temperatures 
 // Serial.print("Temperature for the device 1 (index 0) is: ");
  float x=sensors.getTempCByIndex(0);
//  Serial.println(x);  
   lcd.setCursor(0,0);
    lcd.print("Temperature: "); 
      lcd.setCursor(0,1);
      lcd.print("          ");
        lcd.setCursor(0,1); 
    lcd.print(x);        
}
