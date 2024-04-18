#include <servo.h>
class Engine{
    private:
    const int8_t motor1_port = 4;
    const int8_t motor2_port = 5;
    const int8_t motor3_port = 6;
    const int8_t motor4_port = 7;
    Servo motor1;
    Servo motor2;
    Servo motor3;
    Servo motor4;

    public:
    Engine();
    void setMotorSpeed(int16_t motor1_speed, int16_t motor2_speed, int16_t motor3_speed, int16_t motor4_speed);
    void intializeEngine();
    void setMotor1Speed(int16_t motor1_speed);
    void setMotor2Speed(int16_t motor2_speed);
    void setMotor3Speed(int16_t motor3_speed);
    void setMotor4Speed(int16_t motor4_speed);
    
};