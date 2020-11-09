#ifndef IMAGEBUILDER_H
#define IMAGEBUILDER_H

#include <cstdint>
#include <cstring>
#include <string>

class ImageBuilder {
    public:
        ImageBuilder(int width, int max);
        ~ImageBuilder();
        void pushRow(uint8_t *in, int len, int shift);
        void saveImage(std::string filename, bool resize);
        void cloneLastRow(int ntimes);
        void despeckle();
        int rows;
    private:
        int width;
        int maxRows;
        unsigned short *imageBuffer;
        uint16_t *rowBuffer;
        void unpack10(uint8_t *in, int len, uint16_t *out);
};

#endif
