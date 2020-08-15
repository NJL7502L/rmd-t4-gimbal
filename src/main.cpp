#include <Arduino.h>
#include "../lib/FlexCAN_T4_manager/FlexCAN_T4_manager.h"

FlexCAN_T4_manager* canmanager = FlexCAN_T4_manager::getInstance();

void setup(){
  canmanager->init(false,false,true);
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop(){
  delay(500);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN,LOW);
  uint32_t canid = 0;
  uint8_t data[8] = {};
  canmanager->readAll();
  canmanager->getBus1(canid,data);
}