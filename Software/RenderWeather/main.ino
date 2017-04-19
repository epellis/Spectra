#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 1

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB pixels[NUM_LEDS];

void setup() {
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  	  FastLED.addLeds<NEOPIXEL, DATA_PIN>(pixels, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  // Turn the LED on, then pause
  pixels[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  pixels[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}

// #include <FastLED.h>
//
// #define DATA_PIN          3
// #define LED_TYPE          WS2812B
// #define COLOR_ORDER       GRB
// #define NUM_LEDS          64
// #define SIDE_LENGTH       8
// #define BRIGHTNESS        48
// #define FRAMES_PER_SECOND 60
//
// int temperature;
// int humidity;
//
// int is_windy[NUM_LEDS];
// float true_x[NUM_LEDS];
// float true_y[NUM_LEDS];
// float period[NUM_LEDS];
//
// // int * get_colors(int temperature) {
// //   int rgb[3];
// //   rgb[0] = temperature;
// //   rgb[1] = temperature / 2 + 128;
// //   rgb[2] = 255 - temperature;
// // }
// //
// // void prepare_leds() {
// //   for (int i = 0; i < NUM_LEDS; i++) {
// //     int rgb[3] = get_colors(temperature);
// //     leds[i] = CRGB(rgb[0], rgb[1], rgb[2]);
// //     true_x[i] = i % SIDE_LENGTH;
// //     true_y[i] = i / SIDE_LENGTH;
// //     period[i] = 0;
// //   }
// // }
//
// void setup() {
//   // prepare_leds();
//   FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
//   for (int i = 0; i < NUM_LEDS; i++) {
//     leds[i] = CRGB::Blue;
//   }
//   FastLED.setBrightness(BRIGHTNESS);
// }
//
// void loop() {
//   FastLED.show();
//   FastLED.delay(1000 / FRAMES_PER_SECOND);
// }
