#ifndef HEADER_H
#define HEADER_H

#include <cstdint>
#include <time.h>

struct Header {
    uint8_t BlockID;
    uint8_t WordSize;
    uint16_t WordCount;
    uint16_t ProductID;
    bool RepeatFlag;
    uint8_t VersionNumber;
    bool DataValid;
    bool ASCII;
    uint8_t SPSID;
    uint8_t RangeWord; // Actually two 4 bit values used for completely different things, gee, thanks NOAA
    uint16_t BlockCount;
    time_t SPSTime;
    uint16_t ErrorCheck;
};

class HeaderParser {
    public:
        Header parse(uint8_t *in);
        HeaderParser(unsigned int offset);
    private:
        unsigned int offset;
        inline uint16_t Uint8ToUint16(uint8_t *in);
        time_t ParseBCDTime(uint8_t *in);
};

#endif