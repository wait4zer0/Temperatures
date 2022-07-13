 #include <OneWire.h>  
 #include <DallasTemperature.h>  
 #include <Wire.h>   
 #include <TM74HC595Display.h>
 #include <TimerOne.h>

 #define ONE_WIRE_BUS 2


 int SCLK = 5;
 int RCLK = 6;
 int DIO = 7;

 TM74HC595Display disp(SCLK, RCLK, DIO);
unsigned char SYM[39];

 OneWire oneWire(ONE_WIRE_BUS);  
 DallasTemperature sensors(&oneWire);  
  float Celcius=0.0;  
 void setup(void)  
 {  
  symbols();

  
  Timer1.initialize(1500); // set a timer of length 1500
  Timer1.attachInterrupt(timerIsr); // attach the service routine here 
  sensors.begin();  
  if (sensors.getDS18Count() == 0){
      disp.set(SYM[24], 3);
      delay(1000);
      disp.set(SYM[38], 2);
      delay(2000);
      disp.set(SYM[38], 1);
      delay(3000);
      disp.set(SYM[38], 0);
      delay(4000);
  }

   else
      sensors.setResolution(12);
  
 }  
 void loop(void)  
 {   
  if (sensors.getDS18Count() != 0) {
      sensors.requestTemperatures();   
      double Celcius=sensors.getTempCByIndex(0);  

  
      disp.float_dot(Celcius,2);

  }
  
  delay(2000);  
 }

void timerIsr()
{
  disp.timerIsr();
}

void symbols() {
  // numbers
  SYM[0] = 0xC0; //0
  SYM[1] = 0xF9; //1
  SYM[2] = 0xA4; //2
  SYM[3] = 0xB0; //3
  SYM[4] = 0x99; //4
  SYM[5] = 0x92; //5
  SYM[6] = 0x82; //6
  SYM[7] = 0xF8; //7
  SYM[8] = 0x80; //8
  SYM[9] = 0x90; //9

  // dot numbers
  SYM[10] = 0b01000000; //0.
  SYM[11] = 0b01111001; //1.
  SYM[12] = 0b00100100; //2.
  SYM[13] = 0b00110000; //3.
  SYM[14] = 0b00011001; //4.
  SYM[15] = 0b00010010; //5.
  SYM[16] = 0b00000010; //6.
  SYM[17] = 0b01111000; //7.
  SYM[18] = 0b00000000; //8.
  SYM[19] = 0b00010000; //9.

  // charcter
  SYM[20] = 0x88; //A
  SYM[21] = 0x83; //b
  SYM[22] = 0xC6; //C
  SYM[23] = 0xA1; //d
  SYM[24] = 0x86; //E
  SYM[25] = 0x8E; //F
  SYM[26] = 0xC2; //G
  SYM[27] = 0x89; //H
  SYM[28] = 0xF9; //I
  SYM[29] = 0xF1; //J
  SYM[30] = 0xC3; //L
  SYM[31] = 0xA9; //n
  SYM[32] = 0xC0; //O
  SYM[33] = 0x8C; //P
  SYM[34] = 0x98; //q
  SYM[35] = 0x92; //S
  SYM[36] = 0xC1; //U
  SYM[37] = 0x91; //Y
  SYM[38] = 0b11110111; // _
}
