struct MotorPowers {
  int frontLeftMotorPower;
  int frontRightMotorPower;
  int rearLeftMotorPower;
  int rearRightMotorPower;
};

void intializeEngine();
void spinMotors(struct MotorPowers motorPowers);
void stopMotors();  