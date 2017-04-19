#include <FastLED.h>

#define DATA_PIN          3
#define LED_TYPE          WS2812B
#define COLOR_ORDER       GRB
#define NUM_LEDS          64
#define SIDE_LENGTH       8
#define BRIGHTNESS        42
#define FRAMES_PER_SECOND 10

int count = 0;

CRGB leds[NUM_LEDS];
int is_windy[NUM_LEDS];
float true_x[NUM_LEDS];
float true_y[NUM_LEDS];
float period[NUM_LEDS];
int fade[NUM_LEDS];

void prepare_leds() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Azure;
    leds[i].fadeLightBy(64 * abs(count % i));
  }
}

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  prepare_leds();
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  if (count < NUM_LEDS * 256) {
    count++;
  } else count = 0;
}
