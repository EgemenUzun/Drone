#include <stdint.h>
class ReciverLib{
    public:
    
    //default constructor
    ReciverLib();

    //getters
    int16_t getThrottle();
    int16_t getYaw();
    int16_t getPitch();
    int16_t getRoll();
    bool getswitchA();
    bool getswitchB();
    //setters
    void setThrottle(int16_t throttle);
    void setYaw(int16_t yaw);
    void setChannelValues(int16_t channel_values[6]);

    //reciver channel ports in arduino
    const int8_t channel1_port = 8; // Roll  
    const int8_t channel2_port = 9; // Pitch 
    const int8_t channel3_port = 10; // Throttle
    const int8_t channel4_port = 11; // Yaw
    const int8_t channel5_port = 12; // Switch A
    const int8_t channel6_port = 13; // Switch B

    private:

    //convert channel to value
    void covertChannelsToValue(); 

    //reciver inputs
    const int16_t min_reciver_input = 997;
    const int16_t max_reciver_input = 1972;

    //reciver values
    int16_t throttle = 0;
    int16_t yaw = 0;
    int16_t pitch = 0;
    int16_t roll = 0;
    bool switchA = 0;
    bool switchB = 0;

    //channel values
    int16_t channel_values[6];
};