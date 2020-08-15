#include <Arduino.h>
#include <MsTimer2.h>
#include "../lib/FlexCAN_T4_manager/FlexCAN_T4_manager.h"

FlexCAN_T4_manager* canmanager = FlexCAN_T4_manager::getInstance();

union FtoC{
  float f;
  uint8_t c[4];
};
FtoC pitch, roll, yaw;

void timerInt(){
  uint8_t data[8] = {};
  canmanager->readBus3();

  canmanager->getBus3(0x0A,data);
  pitch.c[0] = data[0];
  pitch.c[1] = data[1];
  pitch.c[2] = data[2];
  pitch.c[3] = data[3];
  roll.c[0] = data[4];
  roll.c[1] = data[5];
  roll.c[2] = data[6];
  roll.c[3] = data[7];
  canmanager->getBus3(0x0B,data);
  yaw.c[0] = data[0];
  yaw.c[1] = data[1];
  yaw.c[2] = data[2];
  yaw.c[3] = data[3];
}

void setup(){
  canmanager->init(false,false,true);
  Serial.begin(115200);

  pinMode(LED_BUILTIN,OUTPUT);

  MsTimer2::set(1, timerInt);
  MsTimer2::start();
}

void printTitleValue(const char* str,float val){
  Serial.print(str);
  Serial.print(" :\t");
  Serial.print(val);
  Serial.print("\t");
}

void debugPrint(){
  printTitleValue("yaw",yaw.f);
  printTitleValue("pitch",pitch.f);
  printTitleValue("roll",roll.f);
  Serial.println();
}

void loop(){
  delay(100);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN,LOW);
  debugPrint();
}