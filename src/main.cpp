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

    // Serial.print("MPU values: ");
    // Serial.print("Error:");
    // Serial.print(imu_values.Error);
    // Serial.print(",");

    // // Serial.println("----------Controller------------");
    // Serial.print("Yaw Ref:");
    // Serial.print(receiverCommands.YawAngle);
    // Serial.print(",");

    // Serial.print("Pitch Ref:");
    // Serial.print(receiverCommands.PitchAngle);
    // Serial.print(",");

    // Serial.print("Roll Ref:");
    // Serial.print(receiverCommands.RollAngle);
    // Serial.println();
    
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
     if(receiverCommands.YawAngle>1){
      Serial.print("Positive Yaw:");
      Serial.println(receiverCommands.YawAngle);
      Serial.println("-----------------------------");
    } else if(receiverCommands.YawAngle<-1){
      Serial.print("Negative Yaw:");
      Serial.println(receiverCommands.YawAngle);
      Serial.println("-----------------------------");
    }
    Serial.print("MPU values: ");
    Serial.print("Yaw:");
    Serial.print(imu_values.CurrentOrientation.YawAngle);
    Serial.print(",");

    Serial.print("Pitch:");
    Serial.print(imu_values.CurrentOrientation.PitchAngle);
    Serial.print(",");

    Serial.print("Roll:");
    Serial.print(imu_values.CurrentOrientation.RollAngle);
    Serial.print(",");

    Serial.print("FrL:");
    Serial.print(motorPowers.frontLeftMotorPower);
    Serial.print(",");

    Serial.print("FrR:");
    Serial.print(motorPowers.frontRightMotorPower);
    Serial.print(",");

    Serial.print("ReL:");
    Serial.print(motorPowers.rearLeftMotorPower);
    Serial.print(",");

    Serial.print("ReR:");
    Serial.println(motorPowers.rearRightMotorPower);
    Serial.println();
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

}
