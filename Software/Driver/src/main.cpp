#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 64
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop()
{
  int accentIndex = random8();

  while (1) {
    CRGB accentColor = ColorFromPalette(PartyColors_p, accentIndex, 255);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = accentColor;
      FastLED.show();
      delay(10);
    }
    accentIndex += random8(16);
  }
}
