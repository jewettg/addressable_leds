#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    200
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

// This example shows several ways to set up and use 'palettes' of colors with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just run this sketch, 
// and watch the pretty lights as you then read through the code.  Although this sketch has 
// eight (or more) different color schemes, the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
extern const TProgmemPalette16 ut_longhorn_palette_p PROGMEM;
extern const TProgmemPalette16 txam_aggie_palette_p PROGMEM;
extern const TProgmemPalette16 tamuk_palette_p PROGMEM;
extern const TProgmemPalette16 schreiner_palette_p PROGMEM;
extern const TProgmemPalette16 holidayPalette_p PROGMEM;

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}


void loop()
{
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = ut_longhorn_palette_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { currentPalette = txam_aggie_palette_p;    currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { currentPalette = tamuk_palette_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = schreiner_palette_p;     currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = holidayPalette_p;        currentBlending = LINEARBLEND; }
        if( secondHand == 60)  { currentPalette = holidayPalette_p;        currentBlending = LINEARBLEND; }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function sets up a palette of holiday colors (red, green and yellow) stripes.
void SetupHolidayPalette()
{
    CRGB holiday_red = CHSV( HUE_RED, 255, 255);
    CRGB holiday_green  = CHSV( HUE_GREEN, 255, 255);
    CRGB holiday_yellow  = CHSV( HUE_YELLOW, 255, 255);
    
    currentPalette = CRGBPalette16( holiday_green,  holiday_green,  holiday_yellow,  holiday_yellow,
                                    holiday_red, holiday_red, holiday_green,  holiday_green,
                                    holiday_yellow,  holiday_yellow,  holiday_red,  holiday_red,
                                    holiday_green, holiday_green, holiday_yellow,  holiday_yellow);
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 holidayPalette_p PROGMEM =
{
    CRGB::Green,
    CRGB::Green, 
    CRGB::Yellow,
    CRGB::Yellow,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Green,
    CRGB::Green,
    
    CRGB::Yellow,
    CRGB::Yellow,
    CRGB::Red,
    CRGB::Red,

    CRGB::Green,
    CRGB::Yellow,
    CRGB::Red,
    CRGB::Green
};

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,

    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};

const TProgmemPalette16 ut_longhorn_palette_p PROGMEM =
{
    CRGB::OrangeRed,
    CRGB::LightGrey, 
    CRGB::DarkGray,
    CRGB::OrangeRed,
    
    CRGB::OrangeRed,
    CRGB::LightGrey,
    CRGB::DarkGray,
    CRGB::OrangeRed,
    
    CRGB::OrangeRed,
    CRGB::LightGrey,
    CRGB::DarkGray,
    CRGB::OrangeRed,

    CRGB::OrangeRed,
    CRGB::LightGrey,
    CRGB::DarkGray,
    CRGB::OrangeRed
};

const TProgmemPalette16 txam_aggie_palette_p PROGMEM =
{
    CRGB::Maroon,
    CRGB::Maroon, // 'white' is too bright compared to red and blue
    CRGB::LightGrey,
    CRGB::LightGrey,
    
    CRGB::Maroon,
    CRGB::Maroon,
    CRGB::LightGrey,
    CRGB::LightGrey,
    
    CRGB::Maroon,
    CRGB::Maroon,
    CRGB::LightGrey,
    CRGB::LightGrey,

    CRGB::Maroon,
    CRGB::Maroon,
    CRGB::LightGrey,
    CRGB::LightGrey
};

const TProgmemPalette16 tamuk_palette_p PROGMEM =
{
    CRGB::Blue,
    CRGB::Blue, // 'white' is too bright compared to red and blue
    CRGB::Gold,
    CRGB::Gold,
    
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Gold,
    CRGB::Gold,
    
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Gold,
    CRGB::Gold,

    CRGB::Blue,
    CRGB::Blue,
    CRGB::Gold,
    CRGB::Gold
};

const TProgmemPalette16 schreiner_palette_p PROGMEM =
{
    CRGB::Maroon,
    CRGB::LightGrey, // 'white' is too bright compared to red and blue
    CRGB::DarkGray,
    CRGB::Maroon,
    
    CRGB::Maroon,
    CRGB::LightGrey,
    CRGB::DarkGray,
    CRGB::Maroon,
    
    CRGB::Maroon,
    CRGB::LightGrey,
    CRGB::DarkGray,
    CRGB::Maroon,

    CRGB::Maroon,
    CRGB::LightGrey,
    CRGB::DarkGray,
    CRGB::Maroon
};

// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
