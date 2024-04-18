#include <Arduino.h>
#include "reciver.hpp"

ReciverLib myReciver;
void setup() {
  Serial.begin(9600);
  pinMode(myReciver.channel1_port, INPUT);
  pinMode(myReciver.channel2_port, INPUT);
  pinMode(myReciver.channel3_port, INPUT);
  pinMode(myReciver.channel4_port, INPUT);
  pinMode(myReciver.channel5_port, INPUT);
  pinMode(myReciver.channel6_port, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t channelValues[6] = {
    pulseIn(myReciver.channel1_port, HIGH),
    pulseIn(myReciver.channel2_port, HIGH),
    pulseIn(myReciver.channel3_port, HIGH),
    pulseIn(myReciver.channel4_port, HIGH),
    pulseIn(myReciver.channel5_port, HIGH),
    pulseIn(myReciver.channel6_port, HIGH)
  };
  myReciver.setChannelValues(channelValues);
  Serial.print("Throttle: ");
  Serial.println(myReciver.getThrottle());
  Serial.print("Yaw: ");
  Serial.println(myReciver.getYaw());
  Serial.print("Pitch: ");
  Serial.println(myReciver.getPitch());
  Serial.print("Roll: ");
  Serial.println(myReciver.getRoll());
  Serial.print("Switch A: ");
  Serial.println(myReciver.getswitchA());
  Serial.print("Switch B: ");
  Serial.println(myReciver.getswitchB());
  Serial.print("Reciver values: ");
  Serial.print(channelValues[0]);
  Serial.print(",");
  Serial.print(channelValues[1]);
  Serial.print(",");
  Serial.print(channelValues[2]);
  Serial.print(",");
  Serial.println(channelValues[3]);
}
