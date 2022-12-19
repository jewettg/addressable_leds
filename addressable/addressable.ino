#include "FastLED.h"
#define LED_PIN     3
#define NUM_LEDS    200
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

CRGB yellow =  CRGB( 255, 255, 0);
CRGB orange =  CRGB( 255, 128, 0);
CRGB red =     CRGB( 255, 0, 0);
CRGB white =   CRGB( 255, 255, 255);
CRGB green =   CRGB( 0, 153, 0);
CRGB black =   CRGB( 0, 0, 0);

void setup() {
    delay( 3000 ); // power-up safety delay

    // Initialize the LEDs and the FastLED library.
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness( BRIGHTNESS );

    // Setup a random seed for the random number generator.
    randomSeed(analogRead(0));

    // Setup the Built-In LED for debugging
    pinMode(LED_BUILTIN, OUTPUT);

    // Setup the ability to output to the serial console
    Serial.begin(115200);
    while (!Serial);  // wait for serial port to connect. Needed for native USB
    Serial.println("Serial port ready!");
    // Serial OUTPUT:  Serial.println("xxx");
}

void blinkBuiltIn() {
  // Blink the built-in LED
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void twinkle(int pos) {
    for (int r = 0; r < 5; r++) {
      leds[pos] = white;
      FastLED.show();
      delay(20);
      leds[pos] = black;
      FastLED.show();
      delay(20);
    }  
}

void setPixel(int pos, byte red, byte green, byte blue) {
   leds[pos].r = red;
   leds[pos].g = green;
   leds[pos].b = blue;
}

void setAll(CRGB color) {
  for(int pos = 0; pos < NUM_LEDS; pos++ ) {
    leds[pos] = color;
  }
  FastLED.show();    
}


void twinkleRWG(int interations) {

  // Twinkle Setup
  int nLEDs = 10;
  int clrSize = 6;
  CRGB clrList[] = {red, yellow, green, red, yellow, green};
  
  // Set the entire strip to random colors from color list.
  for(int pos = 0; pos < NUM_LEDS; pos++ ) {
    leds[pos] = clrList[random(clrSize)];
  }
  FastLED.show();

  for (int theInt = 0; theInt < interations; theInt++) {

    // Put together a random list of LED positions.
    int tList[nLEDs];
    for ( int mt = 0; mt < nLEDs; mt++ ) {
      tList[mt] = random(NUM_LEDS);
    }

    // Twinkle 'nLEDs' number of LEDs.
    for (int r = 0; r < 5; r++) {
      for ( int mt = 0; mt < nLEDs; mt++ ) {
        leds[tList[mt]] = white;
      }
      FastLED.show();
      delay(20);
      for ( int mt = 0; mt < nLEDs; mt++ ) {
        leds[tList[mt]] = black;
      }
      FastLED.show();
      delay(20);
    }

    // Set 'nLEDs' number of LEDs to random color.
    for ( int mt = 0; mt < nLEDs; mt++ ) {
      leds[tList[mt]] = clrList[random(clrSize)];
    }
    FastLED.show();    
  }
}

void xmasMove(int interations) {
  for (int theInt = 0; theInt < interations; theInt++) {
    int chunk = 40;

    for( int i = 0; i < NUM_LEDS-(chunk*3); i++) {
        for ( int c = i; c < chunk+i; c++) {
          leds[c] = red;
        }
        for ( int c = i+chunk; c < (chunk*2)+i; c++) {
          leds[c] = white;
        }
        for ( int c = i+(chunk*2); c < (chunk*3)+i; c++) {
          leds[c] = green;
        }
        FastLED.show();
        delay(20);
        setAll(black);
    }
    for( int i = NUM_LEDS-(chunk*3); i > 0 ; i--) {
        for ( int c = i; c < chunk+i; c++) {
          leds[c] = red;
        }
        for ( int c = i+chunk; c < (chunk*2)+i; c++) {
          leds[c] = white;
        }
        for ( int c = i+(chunk*2); c < (chunk*3)+i; c++) {
          leds[c] = green;
        }
        FastLED.show();
        delay(20);
        setAll(black);
    }
  }    
}


void loop() { 
  int howMany = 10;

  // Turn everything off.
  setAll(black);

  xmasMove(howMany);
  twinkleRWG(100);


}