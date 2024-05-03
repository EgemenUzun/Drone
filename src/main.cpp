#include <Arduino.h>
#include "reciver.hpp"
#include "engine.hpp"
#include "imu.hpp"

void setup() {
  Serial.begin(9600);
  initializeReciver();
  intializeEngine();
  initializeIMU();
}

void loop() {
  struct ReceiverCommands receiverCommands = GetReceiverCommands();
  struct IMU_Values imu_values = GetIMUvalues();
  Serial.print("Throttle: ");
  Serial.println(receiverCommands.Throttle);
  Serial.print("Yaw: ");
  Serial.println(receiverCommands.YawAngleChange);
  Serial.print("Pitch: ");
  Serial.println(receiverCommands.PitchAngle);
  Serial.print("Roll: ");
  Serial.println(receiverCommands.RollAngle);
  Serial.print("Switch A: ");
  Serial.println(receiverCommands.SwitchA);
  Serial.print("Switch B: ");
  Serial.println(receiverCommands.SwitchD);

  // Serial.print("Reciver values: ");
  // Serial.print("Error:");
  // Serial.print(imu_values.Error);
  // Serial.print(",");

  // Serial.print("Yaw:");
  // Serial.print(imu_values.CurrentOrientation.YawAngle);
  // Serial.print(",");

  // Serial.print("Pitch:");
  // Serial.print(imu_values.CurrentOrientation.PitchAngle);
  // Serial.print(",");

  // Serial.print("Roll:");
  // Serial.print(imu_values.CurrentOrientation.RollAngle);
  // Serial.println();
  delay(100);
}
