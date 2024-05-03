#include <engine.hpp>
#include <servo.h>

//----------- PINS -----------
#define FRONT_LEFT_MOTOR_PIN 4
#define FRONT_RIGHT_MOTOR_PIN 6
#define REAR_LEFT_MOTOR_PIN 5
#define REAR_RIGHT_MOTOR_PIN 7
#define INTERRUPT_PIN 2

//----------- ESC's -----------
#define MIN_MOTOR_PULSE_WIDTH 1000
#define MAX_MOTOR_PULSE_WIDTH 2000


Servo frontLeftMotor;
Servo frontRightMotor;
Servo rearLeftMotor;
Servo rearRightMotor;

void intializeEngine() {
  frontLeftMotor.attach(FRONT_LEFT_MOTOR_PIN, MIN_MOTOR_PULSE_WIDTH, MAX_MOTOR_PULSE_WIDTH);
  frontRightMotor.attach(FRONT_RIGHT_MOTOR_PIN, MIN_MOTOR_PULSE_WIDTH, MAX_MOTOR_PULSE_WIDTH);
  rearLeftMotor.attach(REAR_LEFT_MOTOR_PIN, MIN_MOTOR_PULSE_WIDTH, MAX_MOTOR_PULSE_WIDTH);
  rearRightMotor.attach(REAR_RIGHT_MOTOR_PIN, MIN_MOTOR_PULSE_WIDTH, MAX_MOTOR_PULSE_WIDTH);

  stopMotors();
}

void spinMotors(struct MotorPowers motorPowers) {
  frontLeftMotor.write(motorPowers.frontLeftMotorPower);
  frontRightMotor.write(motorPowers.frontRightMotorPower);
  rearLeftMotor.write(motorPowers.rearLeftMotorPower);
  rearRightMotor.write(motorPowers.rearRightMotorPower);
}

void stopMotors() {
  frontLeftMotor.write(0);
  frontRightMotor.write(0);
  rearLeftMotor.write(0);
  rearRightMotor.write(0);
}