struct ReceiverRawValues {
  int ChannelValues[6];
};
struct ReceiverCommands {
  bool Armed;
  bool Error;
  double Throttle;
  double YawAngleChange;
  double PitchAngle;
  double RollAngle;
  bool SwitchA;
  bool SwitchD;
};
void initializeReciver();
struct ReceiverCommands GetReceiverCommands();
struct ReceiverRawValues getReceiverRawValues();
double map_double(double x, double in_min, double in_max, double out_min, double out_max);
