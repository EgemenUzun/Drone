struct Orientation {
  double Yaw;
  double Pitch;
  double Roll;
  bool Error;
};

void initializeIMU();

struct Orientation getIMUOrientation();

void dmpDataReady();