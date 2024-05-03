struct Orientation {
  double YawAngle;
  double PitchAngle;
  double RollAngle;
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