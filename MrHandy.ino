/*
  Небольшой робот на гусеничных треках и с рукой-манипулятором. Гусеничная платформа и рука - с алиэкспресса
*/

#include "BatCheck.h"
#include "Hand.h"
#include "radio.h"
#include "Motor.h"
#include "LEDEffector.h"

//#define _DEBUG_

Hand        hand{};
BatCheck    bat(A0, 2, 7, A3);
Radio       radio{};
Motor       motor{3, 5, 6, 8};
LEDEffector lamp{};
unsigned long tick;

void setup() {
  lamp.begin();
  tick = millis();
  bat.update(tick);
  radio.begin();
  hand.begin();
  motor.begin();

#ifdef _DEBUG_
  Serial.begin(9600);
#endif  
}

bool prevJ2B    = false;                                                              //флажок для однократной обработки кнопки открытия/закрытия клешни
bool prevB1     = false;                                                              //флажок для однократной обработки кнопки выключателя фар
bool lampState  = false;                                                              //Включены ли фары

void loop() {
  tick = millis();                                                                    //считаем время с момента старта
  if (bat.update(tick)){                                                              //всё хорошо, батарея заряжена, работаем
    if (radio.update()){                                                              //радиосвязь есть
      bat.setBlink(false);                                                            //пульт обнаружен, мигать светодиодом не надо

      if (!radio.SW2()){                                                              //рубильник "умри" выключен
        hand.setSpeed(ID_TURN, map(radio.J2H(), 0, 1023, -50, 50));                   //поворот руки
        hand.setSpeed(ID_FULL_HAND, map(radio.J2V(), 0, 1023, -50, 50));              //наклон
      
        if (radio.BT4()) hand.setSpeed(ID_UP_DOWN, 20);                               //подъём 
        else if (radio.BT3()) hand.setSpeed(ID_UP_DOWN, -20);                         //опускание руки
        else hand.setSpeed(ID_UP_DOWN, 0);                                            //не поднимать и не опускать

        if (radio.J2B())                                                              //обработка нажатия джойстика
          if (!prevJ2B)                                                               
            hand.ClawOpened()?hand.CloseClaw():hand.OpenClaw();                       //открытие/закрытие клешни
        prevJ2B = radio.J2B();

        if (radio.SW1()) hand.setDefaults();                                          //щёлкнули тумблер для выставления руки в положение "по умолчанию"

        hand.update(tick);                                                            //рука обрабатывает данные по углам и скоростям

        int spV = map(constrain(radio.J1V(), 123, 900), 123, 900, -255, 255);         //данные о движении вперёд-назад
        int spH = map(constrain(radio.J1H(), 123, 900), 123, 900, -255, 255);         //данные о движении вправо-влево
        if (spV < 60 && spV > -60) spV = 0;                                           //зона "нуля" на джойстике
        if (spH < 60 && spH > -60) spH = 0;                                           //зона "нуля" на джойстике
        int spL = spV-spH;                                                            //вычисляем скорость
        int spR = spV+spH;                                                            //вычисляем скорость
        motor.setSpeed(spL, spR);                                                     //выставляем скорость
        motor.update();                                                               //обновляем параметры моторов

        if (radio.BT1() && !prevB1)                                                   //обработка выключателя фар
          lampState = !lampState;
        prevB1 = radio.BT1();

        lamp.setBrightness(radio.Pot1()/4);                                           //яркость ламп
        
        if (lampState){
          if (spL > 20) lamp.setDir(DIR_FWD, SIDE_LEFT, tick);                        //отрабатываем состояние левых фар
          else if (spL < -20) lamp.setDir(DIR_BWD, SIDE_LEFT, tick);
          else lamp.setDir(DIR_STOP, SIDE_LEFT, tick);

          if (spR > 20) lamp.setDir(DIR_FWD, SIDE_RIGHT, tick);                       //отрабатываем состояние правых фар
          else if (spR < -20) lamp.setDir(DIR_BWD, SIDE_RIGHT, tick);
          else lamp.setDir(DIR_STOP, SIDE_RIGHT, tick);
        } else {
          lamp.die();
        }
        
        lamp.update();
      } else {
        motor.die();                                                                  //включен тумблер "умри". умираем
        hand.die(tick);                                                               //включен тумблер "умри". умираем
        lamp.die();                                                                   //выключить фары
      }
    } else {
      bat.setBlink(true);                                                             //радиосвязи нет. включаем мигалку
      lamp.die();                                                                     //радиосвязи нет. гасим фары
      motor.die();                                                                    //радиосвязи нет. гасим механику
      hand.die(tick);                                                                 //радиосвязи нет. гасим механику
    }
  } else {
    //заряди батарею!!!
    motor.die();                                                                      //батарея разряжена. выключаем механику
    hand.die(tick);                                                                   //батарея разряжена. выключаем механику
    lamp.die();                                                                       //выключить фары
  }
  /* 
   * ЗАМЕДЛЕНИЕ ВЫПОЛНЕНИЯ КОДА! БЕЗ ЭТОГО НЕ БУДЕТ РАБОТАТЬ ТРЕТЬЯ СЕРВА
   */
   delay(7);
}
