/*
  Простейшая реализация анализа состояния АКБ. Используется делитель напряжения (напряжение АКБ в полностью заряженном состоянии 8.4В). 
  Измерения через АЦП не очень точные, но для спасения батареи этого достаточно
*/

#ifndef __BAT_CHECK__
#define __BAT_CHECK__
#include <Arduino.h>

#define BLINK_INTERVAL  250
#define BAT_OK          0
#define BAT_WARN        1
#define BAT_DISCH       2

#define FILTER_KOEF     0.05f
#define FILTER_KOEF_B   0.5f

class BatCheck {
  private:
    byte            batState;
    int             inp_v;
    int             r, g, y;
    unsigned long   startTime;
    bool            isBlink;
    float           V;
  public:
    BatCheck(int _inp_v, int _r, int _g, int _y);
    bool update(unsigned long T);

    void setBlink(bool _blink){
      isBlink = _blink;
    }

    float getVoltage(){
      return V;
    }
};

#endif //__BAT_CHECK__
