#include "radio.h"

byte address[6] = {"Zpipe"}; 

Radio::Radio(){
  //Do nothing :)
}

void Radio::begin(){
  _reciever.begin();
  _reciever.setAutoAck(1);
  _reciever.setRetries(0,15);

  _reciever.openReadingPipe(1,address);
  _reciever.setChannel(0x30);

  _reciever.setPALevel (RF24_PA_MAX);
  _reciever.setDataRate (RF24_1MBPS);
  
  _reciever.powerUp();
  _reciever.startListening();
}

bool Radio::update(){
  byte  pipeNum;
  bool  res = false;
  if (_err_count < 200) _err_count++;
  while (_reciever.available(&pipeNum)){
    _reciever.read(&_buf, sizeof(_buf));
    res = true;
    _err_count = 0;
  }

  if (!radioOk()){
    _buf.Button1 = 0;
    _buf.Button2 = 0;
    _buf.Button3 = 0;
    _buf.Button4 = 0;
    _buf.Switch1 = 0;
    _buf.Switch2 = 0;
    _buf.Pot1    = 0;
    _buf.Pot2    = 0;
    _buf.J1.button = 0;
    _buf.J1.V = 0;
    _buf.J1.H = 0;
    _buf.J2.button;
    _buf.J2.V = 0;
    _buf.J2.H = 0;
  }

  return res;
}

bool Radio::radioOk(){
  return _err_count < ERR_COUNTER;
}

bool Radio::BT1(){
  return _buf.Button1;
}

bool Radio::BT2(){
  return _buf.Button2;
}

bool Radio::BT3(){
  return _buf.Button3;
}

bool Radio::BT4(){
  return _buf.Button4;
}

bool Radio::SW1(){
  return _buf.Switch1;
}

bool Radio::SW2(){
  return _buf.Switch2;
}

int Radio::Pot1(){
  return _buf.Pot1;
}

int Radio::Pot2(){
  return _buf.Pot2;
}

bool Radio::J1B(){
  return _buf.J1.button;
}

bool Radio::J2B(){
  return _buf.J2.button;
}

int Radio::J1V(){
  return _buf.J1.V;
}

int Radio::J1H(){
  return _buf.J1.H;
}

int Radio::J2V(){
  return _buf.J2.V;
}

int Radio::J2H(){
  return _buf.J2.H;
}
