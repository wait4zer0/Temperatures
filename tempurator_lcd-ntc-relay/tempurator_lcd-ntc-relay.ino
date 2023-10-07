/****************************************/
#include <math.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

/****************************************/
  const int relayPin = 8;
  const int ThermistorPin = A0;
  double Thermistor(int RawADC) {
  double Temp;
 Temp = log(10000.0*((1023.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;          
 //Temp = (Temp * 9.0)/ 5.0 + 32.0; 
 return Temp;
}
/****************************************/
void setup() {
  pinMode(relayPin, OUTPUT);

  lcd.init();                      // initialize the lcd 
  lcd.backlight();

}
void loop() {             
  int val;                
  float  temp;            
  val=analogRead(ThermistorPin);      
  temp=Thermistor(val);
  if (temp >= 25){
    digitalWrite(relayPin, LOW);
    
  }
else {
 
  digitalWrite(relayPin, HIGH);

} 
  lcd.clear();
  delay(500);
  lcd.setCursor(2, 0);
  lcd.print("Temperature");
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(6, 1);
  lcd.print(temp);
  lcd.setCursor(12,1);
  lcd.print("C");
  delay(60000);


}
