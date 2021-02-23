#include "Frames.h"
#include <cstdio>


frame::frame(int ip) {
    this->CFrame = new unsigned char[this->LENGTH];
    SetStartOfFrame();
    SetId(ip);
    CFrame[8] = (char)ip;
    SetLength(LENGTH);
    SetTemperature(0);
    SetPWM(0);
    SetTune(0);
    SetChecksum();
    SetEndOfFrame();
}
frame::frame(unsigned char* RFrame, int ip) {
    this->LENGTH = sizeof(*RFrame);
    this->CFrame = new unsigned char[this->LENGTH];
    SetListIds(RFrame, ip);
    SetStartOfFrame();
    SetId(ip);
}
void frame::SetStartOfFrame() {
    this->CFrame[0] = 0xAA;
    this->CFrame[1] = 0xBB;
}
void frame::SetLength(int length) {
    this->CFrame[2] = (char)sizeof(CFrame);
}
void frame::SetId(int ip) {
    CFrame[3] = (char)ip;
}
void frame::SetTemperature(float temperature) {
    CFrame[4] = 'c';
    CFrame[5] = 'c';
}
void frame::SetPWM(int pwm) {
    CFrame[6] = (char)pwm;
}
void frame::SetTune(int tune) {
    CFrame[7] = (char)tune;
}
void frame::SetListIds(unsigned char* RFrame, int ip) {
    const int newSize = sizeof(RFrame) + 1;
    char newFrame[newSize];
    for (int i = 0; i < sizeof(RFrame); i++) {
        newFrame[i] = RFrame[i];
    }
    // CFrame = newFrame;
    LENGTH = newSize;
    SetChecksum();
    SetEndOfFrame();
}
void frame::SetChecksum() {
    CFrame[LENGTH - 3] = 'a';
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