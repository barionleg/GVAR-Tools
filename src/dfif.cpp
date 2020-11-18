/*
 * NRS-S Differential Decoder
 *
 * Original from Lucas Teske on 25/01/2017
 * Modified by Xerbo for NRZ-S on 07/11/2020
 */

#include "diff.h"

void nrzsDecode(uint8_t *data, int length) {
    uint8_t lastBit = 0;
    uint8_t mask;
    for (int i = 0; i < length; i++) {
        mask = ((data[i] >> 1) & 0x7F) | (lastBit << 7);
        lastBit = data[i] & 1;
        data[i] ^= 255-mask;
    }
}
