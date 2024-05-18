struct MotorPowers calculateMotorPowers(struct ReceiverCommands receiverCommands, struct IMU_Values imu_values);
void resetPidVariables();
double calculateYawError(struct ReceiverCommands receiverCommands, struct IMU_Values imu_values);