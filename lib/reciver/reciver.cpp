#include "reciver.hpp"
#include <Arduino.h>
ReciverLib::ReciverLib(){
    this->throttle = 0;
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->switchA = 0;
    this->switchB = 0;
}

int16_t ReciverLib::getThrottle(){
    return throttle;
}   

int16_t ReciverLib::getYaw(){
    return yaw;
}

int16_t ReciverLib::getPitch(){
    return pitch;
}

int16_t ReciverLib::getRoll(){
    return roll;
}

bool ReciverLib::getswitchA(){
    return switchA;
}

bool ReciverLib::getswitchB(){
    return switchB;
}

void ReciverLib::setThrottle(int16_t throttle){
    this->throttle = throttle;
}

void ReciverLib::setYaw(int16_t yaw){
    this->yaw = yaw;
}

void ReciverLib::setChannelValues(int16_t channel_values[6]){
    for(int i = 0; i < 6; i++){
        this->channel_values[i] = channel_values[i];
    }
    covertChannelsToValue();
}

void ReciverLib::covertChannelsToValue(){
    this->roll = map(this->channel_values[0], this->min_reciver_input, this->max_reciver_input, -20, 20);
    this->pitch = map(this->channel_values[1], this->min_reciver_input, this->max_reciver_input, -20, 20);
    this->throttle = map(this->channel_values[2], this->min_reciver_input, this->max_reciver_input, 0, 180);
    this->yaw = map(this->channel_values[3], this->min_reciver_input, this->max_reciver_input, -20, 20);
    this->switchA = map(this->channel_values[4], this->min_reciver_input, this->max_reciver_input, 0, 1);
    this->switchB = map(this->channel_values[5], this->min_reciver_input, this->max_reciver_input, 0, 1);
}