struct ReceiverRawValues {
  int ChannelValues[6];
};
struct ReceiverCommands {
  bool Armed;
  bool Error;
  int Throttle;
  double YawAngleChange;
  double PitchAngle;
  double RollAngle;
  bool SwitchA;
  bool SwitchD;
};
void initializeReciver();
struct ReceiverCommands GetReceiverCommands();
