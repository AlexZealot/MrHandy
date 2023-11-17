#ifndef __LED_EFFECTOR__
#define __LED_EFFECTOR__

#include <FastLED.h>

#define PIN_LED           4

#define LEDS_COUNT        4

#define SIDE_LEFT         0
#define SIDE_RIGHT        1

#define DIR_FWD           1
#define DIR_BWD           2
#define DIR_STOP          0

class LEDEffector {
  private:
    CRGB    leds[LEDS_COUNT];  
    byte    _brightness;

    void  zeroLEDS(){
      for (int i = 0; i < LEDS_COUNT; i++){
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
      }
    }
    
  public:
    LEDEffector();

    void  begin();
    void  update();
    void  setDir(byte _DIRECTION, byte _SIDE, unsigned long T);
    void  die();
    void  setBrightness(byte _b);
};

#endif //__LED_EFFECTOR__
