/*
 * Generates the pseudo random sequence that is used within GVAR.
 * 
 * By default it generates 10032 bits worth of data and outputs
 * it through stdout, the last 64 bits of that data are used to
 * frame the data in the main program.
 * 
 * Compile with
 *  g++ -o syncgen syncgen.cpp
 */

#include <iostream>
#include <fstream>

template <typename T>
inline bool getBit(T data, int bit) {
    return (data >> bit) & 1;
}

int main(int argc, char *argv[]) {
    uint16_t shifter = 0x53b5; // "The shift register is preset to 51665 octal"

    for (int i = 0; i < 10032; i++){
        bool xor1 = getBit<uint16_t>(shifter, 14);
        bool xor2 = getBit<uint16_t>(shifter, 7);
        bool outBit = xor1 ^ xor2;

        shifter = shifter << 1 | outBit;

        std::cout << outBit;
    }

}
