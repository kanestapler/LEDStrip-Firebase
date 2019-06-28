#include <FastLED.h>
#include <math.h>
#define LED_PIN         7
#define NUM_LEDS        144
#define RED             CRGB(25, 0, 0)
#define BLUE            CRGB(0, 0, 25)
#define GREEN           CRGB(0, 25, 0)
#define YELLOW          CRGB(25, 25, 0)
#define ORANGE          CRGB(25, 12, 0)
#define PURPLE          CRGB(12, 0, 25)
CRGB COLOR_ARRAY[]     {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {
  int arraySize = sizeof(COLOR_ARRAY)/sizeof(COLOR_ARRAY[0]);
  for (int i = 0; i < NUM_LEDS; i++) {
    int interval = NUM_LEDS/(arraySize - 1);
    int arrayIndex = floor(i/interval);
    leds[i] = getColorAtIndex(i%interval, arrayIndex, interval, COLOR_ARRAY);
  }
  leds[NUM_LEDS-1] = COLOR_ARRAY[arraySize-1];
  FastLED.show();
}


CRGB getColorAtIndex(int index, int arrayIndex, int interval, CRGB colorArray[]) {
  float red = getSingleValue(index, colorArray[arrayIndex].red, colorArray[arrayIndex+1].red, interval);
  float green = getSingleValue(index, colorArray[arrayIndex].green, colorArray[arrayIndex+1].green, interval);
  float blue = getSingleValue(index, colorArray[arrayIndex].blue, colorArray[arrayIndex+1].blue, interval);
  return CRGB(red, green, blue);
}

float getSingleValue(int index, int startValue, int endValue, int periodLength) {
  float indexF = float(index);
  float startF = float(startValue);
  float endF = float(endValue);
  float periodF = float(periodLength);
  if (startF < endF) {
    return indexF/periodF * (endF-startF) + startF;
  } else if (endF < startF) {
    return (periodF - indexF)/periodF * (startF -endF) + endF;
  } else {
    return startF;
  }
}

void partyMode() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(random(0,25),random(0,25),random(0,25));
  }
}
