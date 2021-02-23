// Mbed_Testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Frames.h"

void print(unsigned char* list, int length);

int main()
{
    std::cout << "Hello World!\n";

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

    frame* temp = new frame(111);
    temp->SetPWM(100);
    temp->SetTemperature(27);
    temp->SetTune(5);
    temp->SetChecksum();
    temp->SetEndOfFrame();
    unsigned char* data = temp->GetFrame();
    frame* newFrame = new frame(data, 112);
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
        std::cout << (int)list[i] << "\n";
    }
    std::cout << "------------------------" << "\n";
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
