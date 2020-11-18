#ifndef HEADER_H
#define HEADER_H

#include <cstdint>
#include <string>
#include <time.h>

static struct {
    std::string Name[23];
} ProductIDLookup = {{
    "No Data",
    "AAA IR Data",
    "AAA Visible Data",
    "GVAR Imager Documentation", 
    "GVAR Imager IR Data",
    "GVAR Imager Visible Data",
    "GVAR Sounder Documentation",
    "GVAR Sounder Scan Data",
    "GVAR Compensation Data",
    "GVAR Telemetry Statistics",
    "Not Used",
    "GIMTACS Text",
    "SPS Text",
    "AAA Sounding Products",
    "GVAR ECAL Data",
    "GVAR Spacelook Data",
    "GVAR BB Data",
    "GVAR Calibration Coefficients",
    "GVAR Visible NLUTs",
    "GVAR Star Sense Data",
    "GVAR Imager Factory Coefficients",
    "Unassigned",
    "Invalid ID"
}};

struct Header {
    uint8_t BlockID;
    uint8_t WordSize;
    uint16_t WordCount;
    uint16_t ProductID;
    std::string ProductName;
    bool RepeatFlag;
    uint8_t VersionNumber;
    bool DataValid;
    bool ASCII;
    uint8_t SPSID;
    // Actually two 4 bit values used for (afaik) completely different things
    uint8_t RangeWord;
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