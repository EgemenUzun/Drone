struct Orientation {
  double YawAngle = 0;
  double PitchAngle = 0;
  double RollAngle = 0;
};

struct IMU_Values {
  bool Error;
  bool NewDataAvailable;
  double DeltaTimeInSeconds;
  struct Orientation CurrentOrientation;
  struct Orientation PreviousOrientation;
};

void initializeIMU();
struct IMU_Values GetIMUvalues();