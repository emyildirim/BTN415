// bitfields.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


void display(unsigned char bitregister) {
    for (int k = 0; k < 8; k++) {
        //always outputs the rightmost bit
        std::cout << (int)(bitregister >> 7);
        bitregister = bitregister << 1;
    }
    std::cout << std::endl;
}

unsigned char shift_left(unsigned char bitregister,
    int shift, bool use_feedback) {
    unsigned char feedback;
    if (use_feedback) {
        feedback = (bitregister & 0x80) >> 7;
    }
    else {
        feedback = 0;
    }
    return (bitregister << shift) + feedback * use_feedback;
}

unsigned char shift_right(unsigned char bitregister,
    int shift, int use_feedback) {
    unsigned char feedback;
    if (use_feedback) {
        feedback = (bitregister & 0x01) << 7;
    }
    else {
        feedback = 0;
    }
    return (bitregister >> shift) + feedback * use_feedback;
}

unsigned char sum_bits(unsigned char bitregister) {
    unsigned char sum_bits = 0;
    for (int i = 0; i < 8; i++) {
        sum_bits += bitregister & 0x01;
        bitregister = bitregister >> 1;
    }
    return sum_bits;
}

void CRC(unsigned char input, unsigned char& state) {
    unsigned char feedback;
    feedback = ((state & 0x80) >> 7) ^
        ((state & 0x20) >> 5) ^ input;
    state = (state << 1) + feedback;
    std::cout << "state:";
    display(state);
}

int main() {

    unsigned char bitchar;

    int test = 8;
    unsigned char test2 = 15, test3 = 8, test4 = 16;

  
    //basic bitwise operations
    std::cout << "Testing AND" << std::endl;
    display(test);
    display(test2);
    test3 = test & test2;
    display(test3);
    std::cout << "Testing >>" << std::endl;
    display(test);
    test = test >> 1;
    display(test);
    std::cout << "Testing ^" << std::endl;
    display(test2);
    display(test3);
    test4 = test3 ^ test2;
    display(test4);

    //shift right with a feedback loop
    std::cout << "Testing right shift" << std::endl;
    bitchar = 15;
    for (int k = 0; k < 8; k++) {
        display(bitchar);
        bitchar = shift_right(bitchar, 1, true);
        int m = 0;
    }

    //shift left without a feedback loop
    std::cout << "Testing left shift" << std::endl;
    bitchar = 15;
    for (int k = 0; k < 8; k++) {
        display(bitchar);
        bitchar = shift_left(bitchar, 1, false);
    }

    //sum bits
    sum_bits(bitchar);

    //CRC
    unsigned char TxBuffer[128] = {};
    TxBuffer[0] = 4;
    TxBuffer[1] = 4;

    unsigned char bitregister, input, state = 0;
    for (int i = 0; i < 2; i++) {
        bitregister = TxBuffer[i];
        for (int j = 0; j < 8; j++) {
            input = bitregister >> 7;
            CRC(input, state);
            bitregister = bitregister << 1;
        }
    }

    return 0;
}