#include <FastLED.h>
#include <Thread.h>
#include <ThreadController.h>

#define LED_PIN     5
#define NUM_LEDS    24
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

}

void loop() {
  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CHSV( 0, 0, 255);
    FastLED.show();
    delay(10);
    leds[i] = CRGB::Black;
  }
  delay(300);

}
