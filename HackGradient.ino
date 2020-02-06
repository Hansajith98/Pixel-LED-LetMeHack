#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    76
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

CRGBPalette16 currentPalette;

void setup() {
  //delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  setHackPallete();

}

void loop() {
//  uint8_t heatindex = (200);
  static uint8_t startIndex = 76;
  startIndex = startIndex - 2;

  FillLEDsFromPaletteColors( startIndex);

}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 150;

    for ( int j = 76; j >= 0; j--){ 
      leds[j] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
      colorIndex -= 2;
    }
    FastLED.show();
    delay(30);
  }


void setHackPallete() {
  CRGB g1 = CRGB(12, 110, 0);
  CRGB g2  = CRGB(10, 163, 10);
  CRGB g3  = CRGB(23, 178, 16);
  CRGB g4  = CRGB(56, 200, 71);
  CRGB g5  = CRGB(89, 209, 93);
  CRGB g6  = CRGB(115, 224, 135);
  CRGB g7  = CRGB(155, 239, 162);
  CRGB g8  = CRGB(196, 255, 189);

  currentPalette = CRGBPalette16 (
                     g1,  g2,  g3,  g4,
                     g5,  g6,  g7,  g8,
                     g8,  g7,  g6,  g5,
                     g4,  g3,  g2,  g1);
}
