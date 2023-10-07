#include <SoftwareSerial.h>
const int rx=3;
const int tx=4;
SoftwareSerial OpenLog(3, 4); // 1 = Soft RX pin (not used), 4 = Soft TX pin
SoftwareSerial mySerial(rx,tx);
int ThermistorPin = 3;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
pinMode(rx,INPUT);
pinMode(tx,OUTPUT);
mySerial.begin(9600);
OpenLog.begin(9600);
}

void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
 // Tf = (Tc * 9.0)/ 5.0 + 32.0; 


  OpenLog.print(Tc);
  OpenLog.println(" C");
  mySerial.println(Tc);
  mySerial.println(" C");


  delay(30000);
}
