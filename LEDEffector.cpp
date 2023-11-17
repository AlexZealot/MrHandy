#include "LEDEffector.h"

LEDEffector::LEDEffector(){
  
}

void LEDEffector::begin(){
  memset(leds, sizeof(CRGB)*LEDS_COUNT, 0);
  FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, LEDS_COUNT);
  FastLED.setBrightness(255);
  zeroLEDS();
  FastLED.show();
}


void  LEDEffector::update(){
  FastLED.show();  // записываем цвета в ленту  
}

void  LEDEffector::die(){
  zeroLEDS();
  FastLED.show();
}

void  LEDEffector::setBrightness(byte _b){
  _brightness = constrain(_b, 10, 255);
  FastLED.setBrightness(_brightness);
}

void  LEDEffector::setDir(byte _DIRECTION, byte _SIDE, unsigned long T){
  byte col1 = ((T/250)%2 == 0)?0:25;
  byte col2 = ((T/150)%2 == 0)?0:25;
  byte col3 = ((T/350)%2 == 0)?0:25;
  switch (_SIDE){
    case SIDE_LEFT:
      switch (_DIRECTION){
        case DIR_FWD:
          leds[0].r = 255;
          leds[0].g = 0;
          leds[0].b = 0;
          leds[3].r = 255;
          leds[3].g = 255;
          leds[3].b = 255;
          break;
        case DIR_BWD:
          leds[0].r = 255;
          leds[0].g = 255;
          leds[0].b = 255;
          leds[3].r = 255;
          leds[3].g = 0;
          leds[3].b = 0;
          break;
        case DIR_STOP:
          leds[0].r = col1;
          leds[0].g = col2;
          leds[0].b = col3;
          leds[3].r = col3;
          leds[3].g = col2;
          leds[3].b = col1;
          break;
      }
      break;
    case SIDE_RIGHT:
      switch (_DIRECTION){
        case DIR_FWD:
          leds[1].r = 255;
          leds[1].g = 0;
          leds[1].b = 0;
          leds[2].r = 255;
          leds[2].g = 255;
          leds[2].b = 255;
          break;
        case DIR_BWD:
          leds[1].r = 255;
          leds[1].g = 255;
          leds[1].b = 255;
          leds[2].r = 255;
          leds[2].g = 0;
          leds[2].b = 0;
          break;
        case DIR_STOP:
          leds[1].r = col1;
          leds[1].g = col2;
          leds[1].b = col3;
          leds[2].r = col3;
          leds[2].g = col2;
          leds[2].b = col1;
          break;
      }
      break;
  }
}
