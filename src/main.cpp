#include <Arduino.h>
#include "reciver.hpp"
#include "engine.hpp"
#include "imu.hpp"

ReciverLib reciver;
Engine engine;
void setup() {
  Serial.begin(9600);
  pinMode(reciver.channel1_port, INPUT);
  pinMode(reciver.channel2_port, INPUT);
  pinMode(reciver.channel3_port, INPUT);
  pinMode(reciver.channel4_port, INPUT);
  pinMode(reciver.channel5_port, INPUT);
  pinMode(reciver.channel6_port, INPUT);
  reciver.initializeReciver();
  engine.intializeEngine();
  initializeIMU();
}

void loop() {
  // put your main code here, to run repeatedly:
  // int16_t channelValues[6] = {
  //   pulseIn(reciver.channel1_port, HIGH),
  //   pulseIn(reciver.channel2_port, HIGH),
  //   pulseIn(reciver.channel3_port, HIGH),
  //   pulseIn(reciver.channel4_port, HIGH),
  //   pulseIn(reciver.channel5_port, HIGH),
  //   pulseIn(reciver.channel6_port, HIGH)
  // };
  // reciver.setChannelValues(channelValues);
  // engine.setMotorSpeed(reciver.getThrottle(), reciver.getThrottle(), reciver.getThrottle(), reciver.getThrottle());

  // Serial.print("Throttle: ");
  // Serial.println(reciver.getThrottle());
  // Serial.print("Yaw: ");
  // Serial.println(reciver.getYaw());
  // Serial.print("Pitch: ");
  // Serial.println(reciver.getPitch());
  // Serial.print("Roll: ");
  // Serial.println(reciver.getRoll());
  // Serial.print("Switch A: ");
  // Serial.println(reciver.getswitchA());
  // Serial.print("Switch B: ");
  // Serial.println(reciver.getswitchB());
  // Serial.print("Reciver values: ");
  // Serial.print(channelValues[0]);
  // Serial.print(",");
  // Serial.print(channelValues[1]);
  // Serial.print(",");
  // Serial.print(channelValues[2]);
  // Serial.print(",");
  // Serial.println(channelValues[3]);
  // Serial.print(",");
  // Serial.println(channelValues[4]);
  // Serial.print(",");
  // Serial.println(channelValues[5]);

  struct Orientation o = getIMUOrientation();

  Serial.print("Error:");
  Serial.print(o.Error);
  Serial.print(",");

  Serial.print("Yaw:");
  Serial.print(o.Yaw);
  Serial.print(",");

  Serial.print("Pitch:");
  Serial.print(o.Pitch);
  Serial.print(",");

  Serial.print("Roll:");
  Serial.print(o.Roll);
  Serial.println();

  delay(50);
}
