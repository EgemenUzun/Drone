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
    stopMotors();
    resetPidVariables();
    return;
  }

  if (imu_values.NewDataAvailable) {
    struct MotorPowers motorPowers = calculateMotorPowers(receiverCommands, imu_values);

    if(receiverCommands.PitchAngle>1){
      Serial.print("Positive Pitch:");
      Serial.println(receiverCommands.PitchAngle);
      Serial.println("-----------------------------");
    } else if(receiverCommands.PitchAngle<-1){
      Serial.print("Negative Pitch:");
      Serial.println(receiverCommands.PitchAngle);
      Serial.println("-----------------------------");
    }
    if(receiverCommands.RollAngle>1){
      Serial.print("Positive Roll:");
      Serial.println(receiverCommands.RollAngle);
      Serial.println("-----------------------------");
    } else if(receiverCommands.RollAngle<-1){
      Serial.print("Negative Roll:");
      Serial.println(receiverCommands.RollAngle);
      Serial.println("-----------------------------");
    }
     if(receiverCommands.YawAngleChange>1){
      Serial.print("Positive Yaw:");
      Serial.println(receiverCommands.YawAngleChange);
      Serial.println("-----------------------------");
    } else if(receiverCommands.YawAngleChange<-1){
      Serial.print("Negative Yaw:");
      Serial.println(receiverCommands.YawAngleChange);
      Serial.println("-----------------------------");
    }
    Serial.print("Front Left:");
    Serial.print(motorPowers.frontLeftMotorPower);
    Serial.println();

    Serial.print("Front Right:");
    Serial.print(motorPowers.frontRightMotorPower);
    Serial.println();

    Serial.print("Rear Left:");
    Serial.print(motorPowers.rearLeftMotorPower);
    Serial.println();

    Serial.print("Rear Right:");
    Serial.println(motorPowers.rearRightMotorPower);
    Serial.println("-----------------------------");
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
  // delay(100);
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
  // delay(100);
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
