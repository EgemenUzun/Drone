#include <Arduino.h>
#include <reciver.hpp>
#include <engine.hpp>
#include <imu.hpp>
#include <calculate_motor_powers.hpp>
#include <avr/wdt.h>

#define THROTTLE_START_POINT 10  
#define PROGRAM_TIMEOUT_IN_MILLISECONDS WDTO_1S // Watch Dog Timer parameter

void setup() {
  Serial.begin(115200);
  wdt_enable(PROGRAM_TIMEOUT_IN_MILLISECONDS);
  initializeReciver();
  intializeEngine();
  initializeIMU();
}

void loop() {
  wdt_reset();
  struct ReceiverCommands receiverCommands = GetReceiverCommands();
  struct IMU_Values imu_values = GetIMUvalues();

  if (receiverCommands.Error || receiverCommands.Throttle < THROTTLE_START_POINT || !receiverCommands.Armed || imu_values.Error)
  {
    stopMotors();
    resetPidVariables();
    return;
  }

  if (imu_values.NewDataAvailable) {
    struct MotorPowers motorPowers = calculateMotorPowers(receiverCommands, imu_values);
    spinMotors(motorPowers);
  }

  // Serial.print("Throttle: ");
  // Serial.println(receiverCommands.Throttle);
  // Serial.print("Yaw: ");
  // Serial.println(receiverCommands.YawAngleChange);
  // Serial.print("Pitch: ");
  // Serial.println(receiverCommands.PitchAngle);
  // Serial.print("Roll: ");
  // Serial.println(receiverCommands.RollAngle);
  // Serial.print("Switch A: ");
  // Serial.println(receiverCommands.SwitchA);
  // Serial.print("Switch B: ");
  // Serial.println(receiverCommands.SwitchD);

  // // Serial.print("Reciver values: ");
  // // Serial.print("Error:");
  // // Serial.print(imu_values.Error);
  // // Serial.print(",");

  // // Serial.print("Yaw:");
  // // Serial.print(imu_values.CurrentOrientation.YawAngle);
  // // Serial.print(",");

  // // Serial.print("Pitch:");
  // // Serial.print(imu_values.CurrentOrientation.PitchAngle);
  // // Serial.print(",");

  // // Serial.print("Roll:");
  // // Serial.print(imu_values.CurrentOrientation.RollAngle);
  // // Serial.println();
  // delay(100);
}
