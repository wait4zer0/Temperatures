// Tiny RTC (DS1307)
#include <SoftwareSerial.h>
SoftwareSerial OpenLog(0, 5); // 0 = Soft RX pin (not used), 5 = Soft TX pin

#include <Wire.h>    // I2C-Bibliothek einbinden
#include "RTClib.h"  // RTC-Bibliothek einbinden

RTC_DS1307 RTC;      // RTC Modul

#include <OneWire.h>            // OneWire-Bibliothek einbinden
#include <DallasTemperature.h>  // DS18B20-Bibliothek einbinden

#define DS18B20_PIN 9   // Pin für DS18B20 definieren Arduino D2

OneWire oneWire(DS18B20_PIN);          // OneWire Referenz setzen
DallasTemperature sensors(&oneWire);   // DS18B20 initialisieren

void setup(void) {

  // Initialisiere I2C  
  Wire.begin();
  
  // Initialisiere RTC
  RTC.begin();

  // Serielle Ausgabe starten 
  Serial.begin(9600);
  OpenLog.begin(9600);

  // Begrüßungstext auf seriellem Monitor ausgeben
  Serial.println("Starte Datum, Zeit und Temperatur - blog.simtronyx.de");

  // Prüfen ob RTC läuft  
  if (! RTC.isrunning()) {
    
    // Aktuelles Datum und Zeit setzen, falls die Uhr noch nicht läuft
    RTC.adjust(DateTime(__DATE__, __TIME__));
    
    Serial.println("Echtzeituhr wurde gestartet und auf Systemzeit gesetzt.");
  }
  else Serial.println("Echtzeituhr laeuft bereits.");

  sensors.begin();  // DS18B20 starten
}

void loop(){
  
  DateTime now=RTC.now();   // aktuelle Zeit abrufen 
  show_time_and_date(now);  // Datum und Uhrzeit ausgeben
  
  sensors.requestTemperatures();                 // Temperatursensor auslesen
  show_temperature(sensors.getTempCByIndex(0));  // Temperatur ausgeben
  
  delay(30000); // 30 Sekunden warten bis zur nächsten Ausgabe
}

// Wochentag ermitteln
String get_day_of_week(uint8_t dow){ 
  
  String dows="  ";
  switch(dow){
   case 0: dows="SU"; break;
   case 1: dows="MO"; break;
   case 2: dows="TU"; break;
   case 3: dows="WE"; break;
   case 4: dows="TH"; break;
   case 5: dows="FR"; break;
   case 6: dows="SA"; break;
  }
  
  return dows;
}

// Datum und Uhrzeit ausgeben
void show_time_and_date(DateTime datetime){
  
  // Wochentag, Tag.Monat.Jahr
  Serial.print(get_day_of_week(datetime.dayOfTheWeek()));
  OpenLog.print(get_day_of_week(datetime.dayOfTheWeek()));

  Serial.print(", ");
  OpenLog.print(", ");

  if(datetime.day()<10)Serial.print(0);
  Serial.print(datetime.day(),DEC);
  OpenLog.print(datetime.day(),DEC);
  Serial.print(".");
  OpenLog.print(".");
  if(datetime.month()<10)Serial.print(0);
  Serial.print(datetime.month(),DEC);
  OpenLog.print(datetime.month(),DEC);
  Serial.print(".");
  OpenLog.print(".");
  Serial.println(datetime.year(),DEC);
  OpenLog.println(datetime.year(),DEC);
  
  // Stunde:Minute:Sekunde
  if(datetime.hour()<10)Serial.print(0);
  Serial.print(datetime.hour(),DEC);
  OpenLog.print(datetime.hour(),DEC);
  Serial.print(":");
  OpenLog.print(":");
  if(datetime.minute()<10)Serial.print(0);
  Serial.print(datetime.minute(),DEC);
  OpenLog.print(datetime.minute(),DEC);
  Serial.print(":");
  OpenLog.print(":");
  if(datetime.second()<10)Serial.print(0);
  Serial.println(datetime.second(),DEC);
  OpenLog.println(datetime.second(),DEC);
}

// Temperatur ausgeben
void show_temperature(float temp){
  
  Serial.print("Temperatur: ");
  OpenLog.print("Temperature: "); 
  Serial.print(temp);
  OpenLog.print(temp); 

  Serial.print(" ");  // Hier müssen wir ein wenig tricksen
  OpenLog.print(" ");
  Serial.write(176);  // um das °-Zeichen korrekt darzustellen
  Serial.println("C");
  OpenLog.print("C"); 

}
