#include <reciver.hpp>
#include <IBusBM.h>
#include <Arduino.h>

//----------- RECEIVER & TRANSMITTER -----------
#define TRANSMITTER_JOYSTICK_MIN_VALUE 1002
#define TRANSMITTER_JOYSTICK_MAX_VALUE 2000
#define TRANSMITTER_SWITCH_MIN_VALUE 1000
#define TRANSMITTER_SWITCH_MAX_VALUE 2000
#define TRANSMITTER_JOYSTICK_DEAD_BAND 40
#define TRANSMITTER_ARMING_DURATION_IN_MILLISECONDS 1000
#define CHANNEL1_PIN 8  // Roll  
#define CHANNEL2_PIN 9  // Pitch 
#define CHANNEL3_PIN 10 // Throttle
#define CHANNEL4_PIN 11 // Yaw
#define CHANNEL5_PIN 12 // Switch A
#define CHANNEL6_PIN 13 // Switch B

//----------- LIMITS -----------
#define THROTTLE_LIMIT_POINT 180 // between 0-180

double QUADCOPTER_MAX_TILT_ANGLE = 20.00; // roll, pitch tilt angle limit in degrees
double QUADCOPTER_MAX_YAW_ANGLE_CHANGE_PER_SECOND = 180.00;

//----------- TIMEOUTS -----------
#define RECEIVER_COMMUNICATION_TIMEOUT_IN_MILLISECONDS 500

bool armed = false;
unsigned long receiver_last_communication_time = millis();
IBusBM IBus;

void initializeReciver(){
  IBus.begin(Serial);
}


struct ReceiverRawValues getReceiverRawValues() {
  struct ReceiverRawValues v;
  v.ChannelValues[0] = IBus.readChannel(0);
  v.ChannelValues[1] = IBus.readChannel(1);
  v.ChannelValues[2] = IBus.readChannel(2);
  v.ChannelValues[3] = IBus.readChannel(3);
  v.ChannelValues[4] = IBus.readChannel(4); 
  v.ChannelValues[5] = IBus.readChannel(5);
  return v;
}


struct ReceiverCommands getFailureReceiverCommand() {
  struct ReceiverCommands cmd;
  cmd.Error = true;
  return cmd;
}


bool hasArmingStarted = false;
bool hasDisarmingStarted = false;
unsigned long armingStartTime;
unsigned long disarmingStartTime;

//prevent small receiver value changes to affect yaw while joystick is on the center
int ignoreDeadBand(int val) {
  int center = (TRANSMITTER_JOYSTICK_MIN_VALUE + TRANSMITTER_JOYSTICK_MAX_VALUE) / 2;
  if (abs(val - center) <= TRANSMITTER_JOYSTICK_DEAD_BAND)
    return center;
  else
    return val;
}

bool isArming(ReceiverRawValues rawValues) {
  if (map(rawValues.ChannelValues[4], TRANSMITTER_SWITCH_MIN_VALUE, TRANSMITTER_SWITCH_MAX_VALUE, 0, 1) == 1) {
    return true;
  }
  return false;
}


double map_double(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

struct ReceiverCommands GetReceiverCommands() {
  struct ReceiverRawValues receiverRawValues = getReceiverRawValues();
   receiver_last_communication_time = millis();

    struct ReceiverCommands cmd;
    cmd.RollAngle = map_double(receiverRawValues.ChannelValues[0], TRANSMITTER_JOYSTICK_MIN_VALUE, TRANSMITTER_JOYSTICK_MAX_VALUE, -QUADCOPTER_MAX_TILT_ANGLE, QUADCOPTER_MAX_TILT_ANGLE);
    cmd.PitchAngle = -1 * map_double(receiverRawValues.ChannelValues[1], TRANSMITTER_SWITCH_MIN_VALUE, TRANSMITTER_JOYSTICK_MAX_VALUE, -QUADCOPTER_MAX_TILT_ANGLE, QUADCOPTER_MAX_TILT_ANGLE);
    cmd.Throttle = map_double(receiverRawValues.ChannelValues[2], TRANSMITTER_JOYSTICK_MIN_VALUE, TRANSMITTER_JOYSTICK_MAX_VALUE, 0, THROTTLE_LIMIT_POINT);
    cmd.YawAngle = map_double(ignoreDeadBand(receiverRawValues.ChannelValues[3]), TRANSMITTER_JOYSTICK_MIN_VALUE, TRANSMITTER_JOYSTICK_MAX_VALUE, -QUADCOPTER_MAX_YAW_ANGLE_CHANGE_PER_SECOND, QUADCOPTER_MAX_YAW_ANGLE_CHANGE_PER_SECOND);
    cmd.SwitchA = map(receiverRawValues.ChannelValues[4], TRANSMITTER_SWITCH_MIN_VALUE, TRANSMITTER_SWITCH_MAX_VALUE, 0, 1);
    cmd.SwitchD = map(receiverRawValues.ChannelValues[5], TRANSMITTER_SWITCH_MIN_VALUE, TRANSMITTER_SWITCH_MAX_VALUE, 0, 1);
    cmd.Armed = isArming(receiverRawValues);
    cmd.Error = false;

  if (millis() - RECEIVER_COMMUNICATION_TIMEOUT_IN_MILLISECONDS > receiver_last_communication_time) {
    return getFailureReceiverCommand();
  } else if(cmd.Throttle> THROTTLE_LIMIT_POINT){
    cmd.Throttle = 0;
    cmd.Error = true;
    return cmd;
  } else {
    return cmd;
  }
}