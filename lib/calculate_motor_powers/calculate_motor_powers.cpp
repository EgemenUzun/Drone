#include <calculate_motor_powers.hpp>
#include <engine.hpp>
#include <pid.hpp>
#include <imu.hpp>
#include <reciver.hpp>
#include <Arduino.h>

//----------- LIMITS -----------
double const QUADCOPTER_MAX_TILT_ANGLE = 20.00; // roll, pitch tilt angle limit in degrees
double const QUADCOPTER_MAX_YAW_ANGLE_CHANGE_PER_SECOND = 180.00;

//----------- PID CONFIGURATION-----------
double KP_roll_pitch = 0.30;
double KI_roll_pitch = 0.10;
double KD_roll_pitch = 0.10;

double KP_yaw = 0.40;
double KI_yaw = 0.50;
double KD_yaw = 0.00;

//----------- PID CONTROL LIMITS-----------
double ROLL_PITCH_CONTROL_SIGNAL_LIMIT = KP_roll_pitch * QUADCOPTER_MAX_TILT_ANGLE * 2;

//----------- PID VARIABLES -----------
double roll_pid_i, roll_last_error, pitch_pid_i, pitch_last_error, yaw_pid_i, yaw_last_error;
double roll_control_signal, pitch_control_signal, yaw_control_signal;

void resetPidVariables() {
  roll_pid_i = 0;
  roll_last_error = 0;
  pitch_pid_i = 0;
  pitch_last_error = 0;
  yaw_pid_i = 0;
  yaw_last_error = 0;
}

double fix360degrees(double val) {
  if (val > 180) {
    return val - 360;
  } else if (val < -180) {
    return val + 360;
  } else {
    return val;
  }
}

struct MotorPowers reduceMotorPowers(MotorPowers motorPowers) { // to preserve balance if throttle limit exceeds the max value (180)
  int maxMotorPower = max(max(motorPowers.frontLeftMotorPower, motorPowers.frontRightMotorPower), max(motorPowers.rearLeftMotorPower, motorPowers.rearRightMotorPower));
  if (maxMotorPower > 180) {
    double power_reduction_rate = (double)maxMotorPower / (double)180;
    motorPowers.frontLeftMotorPower = round((double)motorPowers.frontLeftMotorPower / power_reduction_rate);
    motorPowers.frontRightMotorPower = round((double)motorPowers.frontRightMotorPower / power_reduction_rate);
    motorPowers.rearLeftMotorPower = round((double)motorPowers.rearLeftMotorPower / power_reduction_rate);
    motorPowers.rearRightMotorPower = round((double)motorPowers.rearRightMotorPower / power_reduction_rate);
  }
  return motorPowers;
}

struct MotorPowers calculateMotorPowers(struct ReceiverCommands receiverCommands, struct IMU_Values imu_values) {
  // calculate orientation errors (error: difference between desired orientation and actual orientation)
  double rollError = receiverCommands.RollAngle - imu_values.CurrentOrientation.RollAngle;
  double pitchError = receiverCommands.PitchAngle - imu_values.CurrentOrientation.PitchAngle;
  double yawError =  receiverCommands.YawAngleChange - fix360degrees(imu_values.CurrentOrientation.YawAngle);

  // calculate control gains based on errors
  roll_control_signal = getControlSignal(rollError, KP_roll_pitch, KI_roll_pitch, KD_roll_pitch, roll_pid_i, roll_last_error, imu_values.DeltaTimeInSeconds);
  pitch_control_signal = getControlSignal(pitchError, KP_roll_pitch, KI_roll_pitch, KD_roll_pitch, pitch_pid_i, pitch_last_error, imu_values.DeltaTimeInSeconds);
  yaw_control_signal = getControlSignal(yawError, KP_yaw, KI_yaw, KD_yaw, yaw_pid_i, yaw_last_error, imu_values.DeltaTimeInSeconds);

  // limit roll-pitch control signals
  roll_control_signal = constrain(roll_control_signal, -ROLL_PITCH_CONTROL_SIGNAL_LIMIT, ROLL_PITCH_CONTROL_SIGNAL_LIMIT);
  pitch_control_signal = constrain(pitch_control_signal, -ROLL_PITCH_CONTROL_SIGNAL_LIMIT, ROLL_PITCH_CONTROL_SIGNAL_LIMIT);
  yaw_control_signal =  constrain(yaw_control_signal, -ROLL_PITCH_CONTROL_SIGNAL_LIMIT, ROLL_PITCH_CONTROL_SIGNAL_LIMIT);
  
  // calculate power for each motor
  struct MotorPowers motorPowers;
  motorPowers.frontLeftMotorPower = round(receiverCommands.Throttle + roll_control_signal + pitch_control_signal - yaw_control_signal);
  motorPowers.frontRightMotorPower = round(receiverCommands.Throttle - roll_control_signal + pitch_control_signal + yaw_control_signal);
  motorPowers.rearLeftMotorPower = round(receiverCommands.Throttle + roll_control_signal - pitch_control_signal + yaw_control_signal);
  motorPowers.rearRightMotorPower = round(receiverCommands.Throttle - roll_control_signal - pitch_control_signal - yaw_control_signal);

  motorPowers = reduceMotorPowers(motorPowers);

  return motorPowers;
}

