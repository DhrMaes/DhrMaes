#include "Frames.h"
#include "Extensions.h"
#include <cstdio>
#include <iostream>


frame::frame(int ip) {
    this->CFrame = new unsigned char[this->LENGTH];
}
frame::frame(int ip, int length) {
    this->LENGTH = length;
    this->CFrame = new unsigned char[this->LENGTH];
}
frame::frame(unsigned char* oldFrame)    {
    if (oldFrame[0] == 0xAA && oldFrame[1] == 0xBB) {
        int l = (int)oldFrame[2];
        if (l >= 12) {
            if (oldFrame[l - 2] == 0xCC && oldFrame[l - 1] == 0xDD) {
                this->LENGTH = l;
                this->CFrame = new unsigned char[l];
                std::copy(oldFrame, oldFrame + l, this->CFrame);
            }
            else {
                this->CFrame = (unsigned char*)"End of frame did not match.";
                this->LENGTH = 0;
            }
        }
        else {
            this->CFrame = (unsigned char*)"Length cannot be shorter then 12 Bytes.";
            this->LENGTH = 0;
        }
    }
    else {
        this->CFrame = (unsigned char*)"Start of frame did not match.";
        this->LENGTH = 0;
    }
}
void frame::SetStartOfFrame() {
    this->CFrame[0] = 0xAA;
    this->CFrame[1] = 0xBB;
}
void frame::SetLength() {
    this->CFrame[2] = (unsigned char)(this->LENGTH);
}
void frame::SetLength(int length) {
    this->LENGTH = length;
    this->CFrame[2] = (unsigned char)(this->LENGTH);
}
void frame::SetId(int ip) {
    CFrame[3] = (unsigned char)ip;
}
void frame::SetTemperature(float temperature) {
    short data = (short)(temperature * 8);
    CFrame[4] = (unsigned char)(data & 0xFF);
    CFrame[5] = (unsigned char)((data >> 8) & 0xFF);
}
void frame::SetPWM(int pwm) {
    CFrame[6] = (unsigned char)pwm;
}
void frame::SetTune(int tune) {
    CFrame[7] = (unsigned char)tune;
}
void frame::SetListIds(int ip) {
    CFrame[this->LENGTH - 4] = (unsigned char)ip;
}
void frame::SetListIds(unsigned char* RFrame, int ip) {
    int length = RFrame[2];
    std::copy(RFrame, RFrame + length, this->CFrame);
    //std::copy(RFrame + 8, RFrame + (length - 4), this->CFrame + 8);
    this->CFrame[this->LENGTH - 4] = (unsigned char)ip;

    //const int newSize = sizeof(RFrame) + 1;
    //char newFrame[newSize];
    //for (int i = 0; i < sizeof(RFrame); i++) {
    //    newFrame[i] = RFrame[i];
    //}
    //CFrame = newFrame;
    //LENGTH = newSize;
    //SetChecksum();
    //SetEndOfFrame();
}
void frame::SetChecksum() {
    unsigned char* rawData = new unsigned char[this->LENGTH - 5];
    std::copy(this->CFrame + 2, this->CFrame + (LENGTH - 3), rawData);
    this->CFrame[LENGTH - 3] = CRC6(rawData, LENGTH - 5);
}
void frame::SetEndOfFrame() {
    CFrame[LENGTH - 2] = 0xCC;
    CFrame[LENGTH - 1] = 0xDD;
}

unsigned char* frame::GetFrame() {
    return CFrame;
}
int frame::GetLength() {
    return LENGTH;
}

#define POLYNOMIAL 0xA6  /* 1010 0110  = x6 + x4 + x + 1 */

static unsigned char CRC6(unsigned char* message, const int length) {
    unsigned char remainder = message[0];
    for (int i = 1; i <= length; i++) {
        for (int bit = 7; bit >= 0; bit--)
        {
            // If the uppermost bit is a 1...
            if (remainder & (1 << 7))
            {
                //XOR the previous remainder with the divisor.
                remainder ^= POLYNOMIAL;
            }
            //Shift the next bit of the message into the remainder.
            remainder = (remainder << 1);
            if (i < length) {
                if (message[i] & (1 << bit) && i < length) {
                    remainder |= 1;
                }
            }
        }
    }
    return (remainder >> 2);
}