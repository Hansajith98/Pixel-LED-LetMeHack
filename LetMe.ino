#include <FastLED.h>
#include <Thread.h>
#include <ThreadController.h>

#define LED_PIN_LET_ME     6
#define NUM_LEDS_LET_ME    161
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB letme[NUM_LEDS_LET_ME];

int hue = 0;
int j;

Thread rainbowT = Thread();
Thread pulseT = Thread();
Thread changeHueT = Thread();

ThreadController control = ThreadController();

void rainbow() {
  uint8_t brightness = 100;

  for ( int i = 0; i < NUM_LEDS_LET_ME; i++) {
    letme[i] = CHSV( hue, 255, brightness);
  }
  FastLED.show();
  //FastLED.delay(10);
}
void pulse() {
  uint8_t brightness = 255;
  int hue1 = hue + 70 ;
  if (hue1 > 255) {
    hue1 -= 255;
  }
  if (j > NUM_LEDS_LET_ME) {
    j = 0;
  }
  letme[j] = CHSV( hue1, 255, brightness);
  FastLED.show();
  FastLED.delay(30);
  j++;


}
void changeHue() {
  if (hue > 255) {
    hue = 0;
  }
  hue++;
}


void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN_LET_ME, COLOR_ORDER>(letme, NUM_LEDS_LET_ME).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  setLetMePallete();


}

void loop() {
  control.run();
}
void setLetMePallete() {
  rainbowT.onRun(rainbow);
  rainbowT.setInterval(50);

  pulseT.onRun(pulse);
  pulseT.setInterval(30);

  changeHueT.onRun(changeHue);
  changeHueT.setInterval(10);

  control.add(&pulseT);
  control.add(&rainbowT);
  control.add(&changeHueT);
}
