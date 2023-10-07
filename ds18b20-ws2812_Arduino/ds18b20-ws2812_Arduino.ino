#include <OneWire.h>
#include <DallasTemperature.h>
#include <FastLED.h>

#define LED_PIN 4
#define NUM_LEDS 1
#define COLOR_ORDER GRB
#define CHIPSET WS2812B

CRGB leds[NUM_LEDS];
OneWire oneWire(2);
DallasTemperature sensors(&oneWire);

float tempThreshold = 25.0;

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  Serial.println("Temperature: " + String(temp) + " C");

  if (temp > tempThreshold) {
    leds[0] = CRGB::Red;
  }
  else {
    leds[0] = CRGB::Blue;
  }
  FastLED.show();
  delay(1000);
}
