const int relayPin = 8;
const int ThermistorPin = A0;
double Thermistor(int RawADC) {
double Temp;
  Temp = log(10000.0*((1023.0/RawADC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;
  // Temp = (Temp * 9.0)/ 5.0 + 32.0; // Farenhite 
 return Temp;
}
/****************************************/
void setup() {
  pinMode(relayPin, OUTPUT);

}
void loop() {             
  int val;                
  double temp;            
  val=analogRead(ThermistorPin);      
  temp=Thermistor(val);
  
  if (temp >= 25){
    digitalWrite(relayPin, LOW);
  }
else {
 
  digitalWrite(relayPin, HIGH);
}
 delay(30000);            
}
