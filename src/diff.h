/*
 * NRS-S Differential Decoder (header file)
 *
 * Original from Lucas Teske on 25/01/2017
 * Modified by Xerbo for NRZ-S on 07/11/2020
 */

#ifndef DIFFERENTIALDECODER_H
#define DIFFERENTIALDECODER_H

#include <cstdint>

void nrzsDecode(uint8_t *data, int length);

#endif