#include <Arduino.h>
#include <MsTimer2.h>
#include "../lib/FlexCAN_T4_manager/FlexCAN_T4_manager.h"
#include "../lib/AliExpressIMU_manager/AliExpressIMU_manager.h"
#include "../lib/GyemsRMD_manager/GyemsRMD_manager.h"

FlexCAN_T4_manager* canmanager = FlexCAN_T4_manager::getInstance();
// AliExpressIMU_manager imu;
GyemsRMD_manager motor;

void timerInt(){
  canmanager->readBus3();
  // imu.read(canmanager);
  motor.read(canmanager);


  uint8_t buf[8] = {0};
  buf[0] = 0x30;
  canmanager->pushBus3(0x141,buf);
  canmanager->writeAll();
}

void setup(){
  canmanager->init(false,false,true);
  Serial.begin(115200);

  pinMode(LED_BUILTIN,OUTPUT);
  motor.setId(1);

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
  // printTitleValue("yaw",imu.yaw);
  // printTitleValue("pitch",imu.pitch);
  // printTitleValue("roll",imu.roll);
  printTitleValue("angleKp",motor.gotData.pid.angleKp);
  printTitleValue("angleKi",motor.gotData.pid.angleKi);
  printTitleValue("speedKp",motor.gotData.pid.speedKp);
  printTitleValue("speedKi",motor.gotData.pid.speedKi);
  printTitleValue("iqKp",motor.gotData.pid.iqKp);
  printTitleValue("iqKi",motor.gotData.pid.iqKi);
  Serial.println();
}

void loop(){
  delay(100);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN,LOW);
  debugPrint();
}
