/*
 * радиоканал с модулем NRF24L01
 * Используется в тандеме с самодельным пультом
 */

#ifndef __RADIO_H__
#define __RADIO_H__

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define ERR_COUNTER 10

//joystick definition
struct  _Joistick {
  byte  button = 0;
  int   V = 0;
  int   H = 0;
};

//data structure
struct DataBuf {
  byte              Button1 = 0;
  byte              Button2 = 0;
  byte              Button3 = 0;
  byte              Button4 = 0;
  byte              Switch1 = 0;
  byte              Switch2 = 0;
  int               Pot1    = 0;
  int               Pot2    = 0;
  _Joistick         J1;
  _Joistick         J2;
};

//Main class
class Radio {
  public:
	  Radio();
	
    void  begin();
    bool  update();

    bool BT1();
    bool BT2();
    bool BT3();
    bool BT4();
    bool SW1();
    bool SW2();
    int  Pot1();
    int  Pot2();
    bool J1B();
    bool J2B();
    int  J1V();
    int  J1H();
    int  J2V();
    int  J2H();

    bool radioOk();
    	
	private:
    RF24	_reciever{10, 9}; //порты для платы с интегрированным NRF24L01

    DataBuf _buf;
    int     _err_count = 0;
};

#endif
