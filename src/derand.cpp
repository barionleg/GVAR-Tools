#include "derand.h"

template <typename T>
inline bool getBit(T data, int bit) {
    return (data >> bit) & 1;
}

// Construction and destruction
GVARDerandomizer::GVARDerandomizer(int length, int byteOffset, uint16_t presetWord){
    derandTable = new bool[length];
    len = length;
    offset = byteOffset;
    initDerandTable(derandTable, len, presetWord);
}
GVARDerandomizer::~GVARDerandomizer(){
    delete[] derandTable;
}

// Generates a boolean array `len` bits long containing the pesudo random sequence
void GVARDerandomizer::initDerandTable(bool *table, int len, uint16_t shifter) {
    for (int i = 0; i < 10032 + len; i++) {
        bool bit = getBit<uint16_t>(shifter, 14) ^ getBit<uint16_t>(shifter, 7);

        shifter = shifter << 1 | bit;

        if (i >= 10032) table[i - 10032] = bit;
    }
}

// Actually perform the PN decode
// TODO: whole byte XORing?
void GVARDerandomizer::work(uint8_t *in){
    int j = 0;
    for (int byten = offset; byten < len/8; byten++) {
        uint8_t buffer = 0;
        for(int i = 7; i >= 0; i--){
            bool bit = getBit(in[byten], i) ^ derandTable[j++];
            buffer |= bit << i;
        }

        in[byten] = (byten % 2 == 0) ? buffer : 255-buffer;

    }
}
