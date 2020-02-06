#include <FastLED.h>
#include <Thread.h>
#include <ThreadController.h>

//--------HACK----------------
#define LED_PIN     4
#define NUM_LEDS_HACK    200
#define BRIGHTNESS  45
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB hack[NUM_LEDS_HACK];
Thread hackT = Thread();


//--------LET ME-------------
#define LED_PIN_LET_ME     5
#define NUM_LEDS_LET_ME    100
#define BRIGHTNESS  45
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB letme[NUM_LEDS_LET_ME];

int hue = 0;
int led_index_let_me;

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
  if (led_index_let_me > NUM_LEDS_LET_ME) {
    led_index_let_me = 0;
  }
  letme[led_index_let_me] = CHSV( hue1, 255, brightness);
  FastLED.show();
  //FastLED.delay(30);
  led_index_let_me++;
}
void changeHue() {
  if (hue > 255) {
    hue = 0;
  }
  hue++;
}

//--------HACK----------------

void hackThread() {
  static uint8_t startIndex = 200;
  startIndex = startIndex - 2;

  FillLEDsFromPaletteColors( startIndex);
}



CRGBPalette16 currentPalette;

void setup() {
  delay( 3000 ); // power-up safety delay

  //--------HACK----------------
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(hack, NUM_LEDS_HACK).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  setHackPallete();
  defineHackThread();

  //--------LET ME-------------
  FastLED.addLeds<LED_TYPE, LED_PIN_LET_ME, COLOR_ORDER>(letme, NUM_LEDS_LET_ME).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  setLetMePallete();



}

void loop() {

  control.run();

}

//--------LET ME-------------
void setLetMePallete() {
  rainbowT.onRun(rainbow);
  rainbowT.setInterval(10);

  pulseT.onRun(pulse);
  pulseT.setInterval(10);

  changeHueT.onRun(changeHue);
  changeHueT.setInterval(10);

  control.add(&pulseT);
  control.add(&rainbowT);
  control.add(&changeHueT);
}

//--------HACK----------------
void defineHackThread() {
  hackT.onRun(hackThread);
  rainbowT.setInterval(5);

  control.add(&hackT);
}


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 150;

  for ( int j = 200; j >= 0; j--) {
    hack[j] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
    colorIndex -= 1;
  }
  FastLED.show();
  delay(10);
}


void setHackPallete() {
  CRGB g1 = CRGB(12, 110, 0);
  CRGB g2  = CRGB(10, 163, 10);
  CRGB g3  = CRGB(80, 178, 16);
  CRGB g4  = CRGB(95, 193, 81);
  CRGB g5  = CRGB(120, 209, 108);
  CRGB g6  = CRGB(145, 224, 135);
  CRGB g7  = CRGB(170, 239, 162);
  CRGB g8  = CRGB(196, 255, 189);

  currentPalette = CRGBPalette16 (
                     g1,  g2,  g3,  g4,
                     g5,  g6,  g7,  g8,
                     g8,  g7,  g6,  g5,
                     g4,  g3,  g2,  g1);
}
