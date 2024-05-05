#include <Arduino.h>
#include <reciver.hpp>
#include <engine.hpp>
#include <imu.hpp>
#include <calculate_motor_powers.hpp>
#include <avr/wdt.h>

#define THROTTLE_START_POINT 10  
#define PROGRAM_TIMEOUT_IN_MILLISECONDS WDTO_1S // Watch Dog Timer parameter

void setup() {
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
    // Serial.println("Error in receiver or IMU values. Stopping motors");
    stopMotors();
    resetPidVariables();
    return;
  }

  if (imu_values.NewDataAvailable) {
    struct MotorPowers motorPowers = calculateMotorPowers(receiverCommands, imu_values);
    // Serial.print("Front Left:");
    // Serial.print(motorPowers.frontLeftMotorPower);
    // Serial.println();

    // Serial.print("Front Right:");
    // Serial.print(motorPowers.frontRightMotorPower);
    // Serial.println();

    // Serial.print("Rear Left:");
    // Serial.print(motorPowers.rearLeftMotorPower);
    // Serial.println();

    // Serial.print("Rear Right:");
    // Serial.print(motorPowers.rearRightMotorPower);
    // Serial.println("-----------------------------");
    spinMotors(motorPowers);
  }

  // Serial.print("Throttle:");
  // Serial.print(receiverCommands.Throttle);
  // Serial.println();

  // Serial.print("PitchAngle");
  // Serial.print(receiverCommands.PitchAngle);
  // Serial.println();

  // Serial.print("RollAngle");
  // Serial.print(receiverCommands.RollAngle);
  // Serial.println();

  // Serial.print("YawAngleChange");
  // Serial.print(receiverCommands.YawAngleChange);
  // Serial.println();
  // struct ReceiverRawValues v = getReceiverRawValues();

  // Serial.print("RAW Throttle:");
  // Serial.print(v.ChannelValues[2]);
  // Serial.println();

  // Serial.print("RAW PitchAngle:");
  // Serial.print(v.ChannelValues[1]);
  // Serial.println();

  // Serial.print("RAW RollAngle:");
  // Serial.print(v.ChannelValues[0]);
  // Serial.println();

  // Serial.print("RAW YawAngleChange:");
  // Serial.print(v.ChannelValues[3]);
  // Serial.println();
  // delay(1000);
  // Serial.print("MPU values: ");
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
}
