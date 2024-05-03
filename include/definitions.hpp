// average flight time is 13 minutes with 10x5 props, 3000 mAh 3S lipo battery






//----------- TIMEOUTS -----------
#define RECEIVER_COMMUNICATION_TIMEOUT_IN_MILLISECONDS 500
#define PROGRAM_TIMEOUT_IN_MILLISECONDS WDTO_1S // Watch Dog Timer parameter

//----------- LIMITS -----------
#define THROTTLE_START_POINT 10  // between 0-180
#define THROTTLE_LIMIT_POINT 180 // between 0-180
double QUADCOPTER_MAX_TILT_ANGLE = 20.00; // roll, pitch tilt angle limit in degrees
double QUADCOPTER_MAX_YAW_ANGLE_CHANGE_PER_SECOND = 180.00;

//----------- PID CONFIGURATION-----------
double KP_roll_pitch = 0.30;
double KI_roll_pitch = 0.10;
double KD_roll_pitch = 0.10;

double KP_yaw = 0.40;
double KI_yaw = 0.50;
double KD_yaw = 0.00;

//----------- PID CONTROL LIMITS-----------
double ROLL_PITCH_CONTROL_SIGNAL_LIMIT = KP_roll_pitch * QUADCOPTER_MAX_TILT_ANGLE * 2;