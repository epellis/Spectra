#include "FastLED.h"

#define DATA_PIN          1
#define LED_TYPE          WS2812B
#define COLOR_ORDER       GRB
#define NUM_LEDS          64
#define POTENIOMETER_PIN   0

CRGB leds[NUM_LEDS];

#define BRIGHTNESS        48
#define FRAMES_PER_SECOND 60

uint32_t startColor = 0xFF512F;
uint32_t endColor = 0xDD2476;

uint8_t pot;

void nextFrame(int st, int ed) {
  fill_gradient_RGB(leds, 0, CRGB(startColor), NUM_LEDS - 1, CRGB(endColor));
}

void setup() {
  /* Initialize Fastled Strip */
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  /* Adjust for brightness */
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  pot = analogRead(POTENIOMETER_PIN);
  fill_solid(leds, NUM_LEDS, HeatColor(pot));
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}
