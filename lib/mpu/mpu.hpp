#include <stdint.h>

class MpuLib {
    public:
        MpuLib();
        void init();
        void read();
        void calibrate();
        void setOffset(int16_t x, int16_t y, int16_t z);
        void setScale(float x, float y, float z);
        void setGyroScale(float x, float y, float z);
        void setAccelScale(float x, float y, float z);
        void setGyroOffset(int16_t x, int16_t y, int16_t z);
        void setAccelOffset(int16_t x, int16_t y, int16_t z);
        void setGyroScale(float x);
        void setAccelScale(float x);
        void setGyroOffset(int16_t x);
        void setAccelOffset(int16_t x);
        void setGyroScale(float x, float y, float z);
        void setAccelScale(float x, float y, float z);
        void setGyroOffset(int16_t x, int16_t y, int16_t z);
        void setAccelOffset(int16_t x, int16_t y, int16_t z);
        void setGyroScale(float x);
        void setAccelScale(float x);
        void setGyroOffset(int16_t x);
        void setAccelOffset(int16_t x);
        void setGyroScale(float x, float y, float z);
        void setAccelScale(float x, float y, float z);
        void setGyroOffset(int16_t x, int16_t y, int16_t z);
        void setAccelOffset(int16_t x, int16_t y, int16_t z);
        void setGyroScale(float x);
        void setAccelScale(float x);
        void setGyroOffset(int16_t x);
        void setAccelOffset(int16_t x);
        void setGyroScale(float x, float y, float z);
        void setAccelScale(float x, float y, float z);
        void setGyroOffset(int16_t x, int16_t y, int16_t z);
        void setAccelOffset(int16_t x, int16_t y, int16_t z);
        void setGyroScale(float x);
        void setAccelScale(float x);
        void setGyroOffset(int16_t x);
        void setAccelOffset(int16_t x);
};