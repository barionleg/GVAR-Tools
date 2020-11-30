#include "imagebuilder.h"

#define cimg_use_png
#define cimg_display 0
#include "CImg.h"

ImageBuilder::ImageBuilder(int width, int maxRows){
    ImageBuilder::width = width;
    ImageBuilder::maxRows = maxRows;
    rows = 0;
    rowBuffer = new uint16_t[width];
    imageBuffer = new unsigned short[width * maxRows];
}
ImageBuilder::~ImageBuilder(){
    delete[] rowBuffer;
    delete[] imageBuffer;
}

// Unpack 5 uint8_t's into 4 uint16_t's containing 10 bit values
void ImageBuilder::unpack10(uint8_t *in, int len, uint16_t *out) {
    /* Every 5 bytes (40 bits) of 'in' will be converted 
     * to 4 16-bits. So put 4 bytes into a 'uint32_t' value
     * and 1 byte in a 'uint8_t' value.
     */
    uint32_t fourBytes;
    uint8_t oneByte;

    // the index for the output string
    int outIndex = 0;
    for (int i = 0; i <= len-5; i += 5) {
        fourBytes = (in[i] << 24) + (in[i + 1] << 16) + (in[i + 2] << 8) + in[i + 3];
        oneByte = in[i + 4];

        uint32_t temp = fourBytes >> 22;
        out[outIndex++] = (uint16_t)temp;

        temp = (fourBytes << 10) >> 22;
        out[outIndex++] = (uint16_t)temp;

        temp = (fourBytes << 20) >> 22;
        out[outIndex++] = (uint16_t)temp;

        temp = ((fourBytes << 30) >> 22) + oneByte;
        out[outIndex++] = (uint16_t)temp;
    }
}

void ImageBuilder::reset() {
    rows = 0;
    std::memset(imageBuffer, 0, width * maxRows * 2);
}

void ImageBuilder::pushRow(uint8_t *in, int len, int shift){
    int posb = 3, x = shift;
    for(int pos = 0; pos < len; pos += 5) {
        uint8_t shiftBuf[5] = { 0 };
        shiftBuf[0] = in[pos + 0] << posb | in[pos + 1] >> (8 - posb);
        shiftBuf[1] = in[pos + 1] << posb | in[pos + 2] >> (8 - posb);
        shiftBuf[2] = in[pos + 2] << posb | in[pos + 3] >> (8 - posb);
        shiftBuf[3] = in[pos + 3] << posb | in[pos + 4] >> (8 - posb);
        shiftBuf[4] = in[pos + 4] << posb | in[pos + 5] >> (8 - posb);

        unpack10(shiftBuf, 5, &rowBuffer[x]);
        x += 4;
    }

    for(int i = 0; i < width; i++){
        imageBuffer[rows*width + i] = rowBuffer[i] * 128;
    }
    rows++;
}

void ImageBuilder::cloneLastRow(int ntimes){
    for(int i = 0; i < ntimes; i++){
        std::memcpy(&imageBuffer[width*(rows+i)], &imageBuffer[width*(rows-1)], width*2);
    }
    rows += ntimes;
}

// "Don't touch what works"
// You can quote me on that later when this breaks or something
void ImageBuilder::despeckle(){
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < width; x++){
            if(imageBuffer[y*width + x] - imageBuffer[y*width + x + 1] > 200 &&
               imageBuffer[y*width + x] - imageBuffer[(y+1)*width + x] > 200){
                imageBuffer[y*width + x] = imageBuffer[y*width + x + 1];
            }
            if(imageBuffer[y*width + x + 1] - imageBuffer[y*width + x] > 200 &&
               imageBuffer[y*width + x - 1] - imageBuffer[y*width + x] > 200){
                imageBuffer[y*width + x] = imageBuffer[y*width + x + 1];
            }
        }
    }
}

void ImageBuilder::saveImage(std::string filename, bool resize) {
    cimg_library::CImg<unsigned short> image = cimg_library::CImg<unsigned short>(imageBuffer, width, rows);
    if(resize){
        image.resize(width, rows*1.75);
    }
    image.save_png(filename.c_str());
}
