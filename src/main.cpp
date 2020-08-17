#include "../lib/AliExpressIMU_manager/AliExpressIMU_manager.h"
#include "../lib/FlexCAN_T4_manager/FlexCAN_T4_manager.h"
#include "../lib/GyemsRMD_manager/GyemsRMD_manager.h"
#include <Arduino.h>
#include <MsTimer2.h>

FlexCAN_T4_manager *canmanager = FlexCAN_T4_manager::getInstance();
// AliExpressIMU_manager imu;
GyemsRMD_manager motor;

void timerInt() {
  canmanager->readBus3();
  // imu.read(canmanager);
  motor.read(canmanager);

  uint8_t buf[8] = {0};
  buf[0] = 0x9C;
  canmanager->pushBus3(0x141, buf);
  canmanager->writeAll();
}

void setup() {
  canmanager->init(false, false, true);
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  motor.setId(1);

  MsTimer2::set(1, timerInt);
  MsTimer2::start();
}

template <typename T> void printTitleValue(const char *str, T val) {
  Serial.print(str);
  Serial.print(" :\t");
  Serial.print(val);
  Serial.print("\t");
}

void debugPrint() {
  // printTitleValue("yaw",imu.yaw);
  // printTitleValue("pitch",imu.pitch);
  // printTitleValue("roll",imu.roll);
  // printTitleValue("angleKp",motor.gotData.pid.angleKp);
  // printTitleValue("angleKi",motor.gotData.pid.angleKi);
  // printTitleValue("speedKp",motor.gotData.pid.speedKp);
  // printTitleValue("speedKi",motor.gotData.pid.speedKi);
  // printTitleValue("iqKp",motor.gotData.pid.iqKp);
  // printTitleValue("iqKi",motor.gotData.pid.iqKi);
  // printTitleValue("Accel",motor.gotData.accel.current);

  // printTitleValue("Enc Current",motor.gotData.encoder.current);
  // printTitleValue("Enc Original",motor.gotData.encoder.original);
  // printTitleValue("Enc Offset",motor.gotData.encoder.offset);
  // printTitleValue("Enc Multi",motor.gotData.angle.multiTurn);
  // printTitleValue("Enc Single",motor.gotData.angle.singleTurn);

  // printTitleValue("temperature",motor.gotData.information.temperature);
  // printTitleValue("voltage",motor.gotData.information.voltage);
  // printTitleValue("LVProtection",motor.gotData.information.error.lowVoltageProtection);
  // printTitleValue("OTProtection",motor.gotData.information.error.overTemperatureProtection);

  printTitleValue("temperature", motor.gotData.information.temperature);
  printTitleValue("speed", motor.gotData.speed.current);
  printTitleValue("torque iq", motor.gotData.torque.iq);
  printTitleValue("encoader", motor.gotData.encoder.current);
  Serial.println();
}

void loop() {
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  debugPrint();
}
