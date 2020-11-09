#ifndef DERAND_H
#define DERAND_H

#include <cstdint>

class GVARDerandomizer {
    public:
        GVARDerandomizer(int length, int byteOffset, uint16_t presetWord);
        ~GVARDerandomizer();
        void work(uint8_t *in);
    private:
        bool *derandTable;
        int offset;
        int len;
        void initDerandTable(bool *table, int len, uint16_t shifter);
        
};

#endif
