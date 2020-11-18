#include "header.h"

HeaderParser::HeaderParser(unsigned int offset) {
    HeaderParser::offset = offset - 1;
}

Header HeaderParser::parse(uint8_t *in) {
    Header header;
    header.BlockID       = in[offset + 1];
    header.WordSize      = in[offset + 2];
    header.WordCount     = Uint8ToUint16(&in[offset + 3]);
    header.ProductID     = Uint8ToUint16(&in[offset + 5]);
    header.RepeatFlag    = in[offset + 7]  == 0;
    header.VersionNumber = in[offset + 8];
    header.DataValid     = in[offset + 9]  == 1;
    header.ASCII         = in[offset + 10] == 1;
    header.SPSID         = in[offset + 11];
    header.RangeWord     = in[offset + 12];
    header.BlockCount    = Uint8ToUint16(&in[offset + 13]);
    header.SPSTime       =  ParseBCDTime(&in[offset + 17]);
    header.ErrorCheck    = Uint8ToUint16(&in[offset + 29]);

    if(header.BlockID == 240) header.BlockID = 0;

    if(header.ProductID <= 20) {
        header.ProductName = ProductIDLookup.Name[header.ProductID];
    } else if(header.ProductID <= 1000) {
        header.ProductName = ProductIDLookup.Name[21];
    } else {
        header.ProductName = ProductIDLookup.Name[22];
    }

    return header;
}

inline uint16_t HeaderParser::Uint8ToUint16(uint8_t *in) {
    return in[0] << 8 | in[1];
}

time_t HeaderParser::ParseBCDTime(uint8_t *in) {
    struct tm time = {0};

    int digits[16] = {0};
    for(int i = 0; i < 8; i++) {
        digits[i*2  ] = in[i] >> 4;
        digits[i*2+1] = in[i] & 0b00001111;
    }

    time.tm_year = digits[0]  * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
    time.tm_year -= 1900;
    time.tm_mday = digits[4]  * 100  + digits[5] * 10  + digits[6];
    time.tm_hour = digits[7]  * 10   + digits[8];
    time.tm_min  = digits[9]  * 10   + digits[10];
    time.tm_sec  = digits[11] * 10   + digits[12];    
    // No millisecond support :(

    return mktime(&time);
}