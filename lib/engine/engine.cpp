#include "engine.hpp"
#include <servo.h>

Engine::Engine(){
}

void Engine::setMotorSpeed(int16_t motor1_speed, int16_t motor2_speed, int16_t motor3_speed, int16_t motor4_speed){
    this->motor1.write(motor1_speed);
    this->motor2.write(motor2_speed);
    this->motor3.write(motor3_speed);
    this->motor4.write(motor4_speed);
}
void Engine::intializeEngine(){
  motor1.attach(this->motor1_port, 1000, 2000);
  motor2.attach(this->motor2_port, 1000, 2000);
  motor3.attach(this->motor3_port, 1000, 2000);
  motor4.attach(this->motor4_port, 1000, 2000);
}