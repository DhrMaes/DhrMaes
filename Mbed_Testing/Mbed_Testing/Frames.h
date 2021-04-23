#pragma once

class frame {
private:
    //unsigned char CFrame[12] = { (unsigned char)0xAA, (unsigned char)0xBB, (unsigned char)0x00, (unsigned char)0x00, (unsigned char)0x00, (unsigned char)0x00, (unsigned char)0x00, (unsigned char)0x00, (unsigned char)0x00, (unsigned char)0x00, (unsigned char)0x00, (unsigned char)0x00 };
    int LENGTH = 12;
    unsigned char* CFrame;
public:
    frame(int ip);
    frame(int ip, int length);
    frame(unsigned char* oldFrame);
    void SetStartOfFrame();
    void SetLength();
    void SetLength(int length);
    void SetId(int ip);
    void SetTemperature(float temperature);
    void SetPWM(int pwm);
    void SetTune(int tune);
    void SetListIds(int ip);
    void SetListIds(unsigned char* RFrame, int ip);
    void SetChecksum();
    void SetEndOfFrame();

    unsigned char* GetFrame();
    int GetLength();
};

static unsigned char CRC6(unsigned char* message, const int length);