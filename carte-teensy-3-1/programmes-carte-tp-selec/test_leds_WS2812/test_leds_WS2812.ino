#include <Adafruit_NeoPixel.h>

#define PIN 6

const int NBR_LEDS = 12 ;
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NBR_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  for (int i=0 ; i<NBR_LEDS ; i++) {
    strip.setPixelColor (i,strip.Color(i * 5, i*5, i*5));
  }
  strip.show();
  delay(2000);

  for (int i=0 ; i<NBR_LEDS ; i++) {
    strip.setPixelColor (i,strip.Color(255, 0, 0));
  }
  strip.show();
  delay(2000);
  
  for (int i=0 ; i<NBR_LEDS ; i++) {
    strip.setPixelColor (i,strip.Color(0, 255, 0));
  }
  strip.show();
  delay(2000);

  for (int i=0 ; i<NBR_LEDS ; i++) {
    strip.setPixelColor (i,strip.Color(0, 0, 255));
  }
  strip.show();
  delay(2000);
  
  for (int i=0 ; i<NBR_LEDS ; i++) {
    strip.setPixelColor (i,strip.Color(random () % 256, random () % 256, random () % 256));
  }
  strip.show();
  delay(2000);
  
}

