// Mbed_Testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Frames.h"
#include "Extensions.h"


void print(unsigned char* list, int length);
unsigned char MOD(unsigned char* list, int length, int mod);

int main()
{
    unsigned char MODTest1[] = { 0x68, 0x01, 0x01 };
    unsigned char MODResult1 = MOD(MODTest1, 3, 256);
    std::cout << std::hex << MODResult1 << "\n";

    //------------------------------------------------------

    std::cout << "Hello World!\n";

    unsigned char crcTest1[] = { 0x0C, 0x65, 0x01, 0x08, 0xE6, 0x01, 0x69 };
    //int crcResult1 = CRC6(crcTest1, 7);

    //------------------------------------------------------

    float ftosh = -22.250;
    short shortTest = (short)(ftosh * 8);
    std::cout << std::hex << shortTest << "\n";

    //------------------------------------------------------

    int mapTest = 168;
    int mapResult = map(mapTest, 0, 255, 0, 100);
    std::cout << mapResult << "\n";

    //-------------------------------------------------------

    unsigned char bitTestData1 = 0xB2;
    unsigned char bitTestData2 = 0xF8;
    //std::cout << std::hex << bitTestData1 << "\n";
    //std::cout << std::hex << bitTestData2 << "\n";
    signed short bitTestResult = bitTestData2 & 0x7;
    bitTestResult <<= 8;
    bitTestResult |= bitTestData1;
    if (((bitTestData2 >> 7) & 0x1) == 1) {
        bitTestResult = -bitTestResult;
    }
    float floatTest = bitTestResult;
    floatTest = floatTest / 8;
    std::cout << bitTestResult << "\n";

    //-----------------------------------------------

    int mapTest1 = map(0, 0, 255, 0, 100);
    std::cout << mapTest1 << "\n";
    int mapTest2 = map(255, 0, 255, 0, 100);
    std::cout << mapTest2 << "\n";
    int mapTest3 = map(100, 0, 255, 0, 100);
    std::cout << mapTest3 << "\n";

    //------------------------------------------------

    int length = 12;
    unsigned char* p;
    p = new unsigned char[length];
    p[0] = 0xBB;
    p[5] = 0xAA;

    print(p, length);
    
    int nlength = length + 1;
    unsigned char* newp;
    newp = new unsigned char[length];
    std::copy(p, p + length, newp);

    print(newp, nlength);
    p = newp;
    print(p, nlength);

    //----------------------------------------------------

    std::cout << "FRAME TESTS" << "\n";
    std::cout << "------------------------" << "\n";

    //----------------------------------------------------

    frame* temp = new frame(111);
    temp->SetStartOfFrame();
    temp->SetLength();
    temp->SetId(111);
    temp->SetTemperature(27);
    temp->SetPWM(100);
    temp->SetTune(5);
    temp->SetListIds(111);
    temp->SetChecksum();
    temp->SetEndOfFrame();
    print(temp->GetFrame(), temp->GetLength());

    frame* newFrame = new frame(112, (int)(temp->GetFrame()[2]) + 1);
    //std::copy(temp->GetFrame(), temp->GetFrame() + temp->GetLength(), newFrame->GetFrame());
    newFrame->SetListIds(temp->GetFrame(), 106);
    newFrame->SetStartOfFrame();
    newFrame->SetLength();
    newFrame->SetId(106);
    newFrame->SetTemperature(27);
    newFrame->SetPWM(100);
    newFrame->SetTune(5);
    //newFrame->SetListIds(106);
    newFrame->SetChecksum();
    newFrame->SetEndOfFrame();
    print(newFrame->GetFrame(), newFrame->GetLength());

    frame* newFrame2 = new frame(newFrame->GetFrame());
    print(newFrame2->GetFrame(), newFrame2->GetLength());

    float value = 27.10235113;
    int ivalue = (int)value;
    int tvalue = (int)(1000 * (value-ivalue));
    std::cout << "192.168.0." + std::to_string(111) << "\n";
    std::cout << value << "\n";
    std::cout << ivalue << "\n";
    std::cout << tvalue << "\n";
}

void print(unsigned char* list, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << std::to_string(i) << "\t" << (int)list[i] << "\n";
    }
    std::cout << "------------------------" << "\n";
}

static long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned char MOD(unsigned char* list, int length, int mod) {
    int val = *list;
    for (int i = 1; i < length; i++)
        val += list[i];
    unsigned char temp = ((65536 - val) % mod);
    return temp;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
