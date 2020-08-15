#include <Arduino.h>
#include <MsTimer2.h>
#include "../lib/FlexCAN_T4_manager/FlexCAN_T4_manager.h"
#include "../lib/AliExpressIMU_manager/AliExpressIMU_manager.h"

FlexCAN_T4_manager* canmanager = FlexCAN_T4_manager::getInstance();
AliExpressIMU_manager IMU;

void timerInt(){
  canmanager->readBus3();
  IMU.read(canmanager);
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
  printTitleValue("yaw",IMU.yaw);
  printTitleValue("pitch",IMU.pitch);
  printTitleValue("roll",IMU.roll);
  Serial.println();
}

void loop(){
  delay(100);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN,LOW);
  debugPrint();
}
