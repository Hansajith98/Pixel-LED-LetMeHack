#include <FastLED.h>

#define LED_PIN_ARROW     3
#define NUM_LEDS_ARROW   126
#define BRIGHTNESS_ARROW  45
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB arrow[NUM_LEDS_ARROW];



//--------Arrow------------
int index = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN_ARROW, COLOR_ORDER>(arrow, NUM_LEDS_ARROW).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS_ARROW );


}

void loop() {
  int arrowIndex[3][2] = {
    {0, 47},
    {47, 85},
    {85, 126}
  };
  for (int j = arrowIndex[index][0]; j < arrowIndex[index][1]; j++) {
    arrow[j] = CRGB::White;
    FastLED.show();
    delay(5);
  }
  delay(300);
  for (int j = arrowIndex[index][0]; j < arrowIndex[index][1]; j++) {
    arrow[j] = CRGB::Black;
    FastLED.show();
    delay(5);
  }
  //delay(100);
  index++;
  if (index > 2) {
    index = 0;

    //------------------------------
    for (int j = arrowIndex[index][0]; j < arrowIndex[index][1]; j++) {
      arrow[j] = CRGB::White;
      FastLED.show();
      delay(5);
    }
    index++;
    for (int j = arrowIndex[index][0]; j < arrowIndex[index][1]; j++) {
      arrow[j] = CRGB::White;
      FastLED.show();
      delay(5);
    }
    index++;
    for (int j = arrowIndex[index][0]; j < arrowIndex[index][1]; j++) {
      arrow[j] = CRGB::White;
      FastLED.show();
      delay(5);
    }
    delay(500);
    index = 0;
    for (int j = arrowIndex[index][0]; j < arrowIndex[index][1]; j++) {
      arrow[j] = CRGB::Black;
      FastLED.show();
      delay(5);
    }
    index++; for (int j = arrowIndex[index][0]; j < arrowIndex[index][1]; j++) {
      arrow[j] = CRGB::Black;
      FastLED.show();
      delay(5);
    }
    index++; for (int j = arrowIndex[index][0]; j < arrowIndex[index][1]; j++) {
      arrow[j] = CRGB::Black;
      FastLED.show();
      delay(5);
    }
    index = 0;
  }
}
