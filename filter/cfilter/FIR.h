/**
 * @file FIR.h
 * @author Krisna Pranav
 * @brief fir
 * @version 1.0
 * @date 2023-09-06
 * 
 * @copyright Copyright (c) 2023 opensatellite-network develoeprs, Krisna Pranav
 * 
 */

#ifndef FILTER_FIR_FILTER_H
#define FILTER_FIR_FILTER_H

#include <stdint.h>

typedef struct 
{
    float out;
	float *coeff;
	float *buf;
	uint8_t order;
	uint8_t putIndex;
}FIRFilter ;

/**
 * @param filt 
 * @param coeff 
 * @param buf 
 * @param order 
 */
void FIRFilter_Init(FIRFilter *filt, float *coeff, float *buf, const uint8_t order) 
{
	filt->out = 0.0f;
	filt->coeff = coeff;
	filt->buf   = buf;
	filt->order = order;
	filt->putIndex = 0;

	for (uint8_t n = 0; n < order; n++) {
		filt->buf[n] = 0.0f;
	}
}

/**
 * @param filt 
 * @param in 
 * @return float 
 */
float FIRFilter_Update(FIRFilter *filt, float in) 
{
    filt->buf[filt->putIndex] = in;

    uint8_t getIndex = filt->putIndex;
    
    filt->out = 0.0f;

    for (uint8_t n = 0; n < filt->order; n++) {
        filt->out = filt->out + filt->coeff[n] * filt->buf[getIndex];
        
        if (getIndex == 0) {
            getIndex = filt->order - 1;
        } else {
           getIndex--; 
        }
    }
    
    filt->putIndex++;

    if (filt->putIndex == filt->order) {
        filt->putIndex = 0;
    }
    
    return filt->out;
}

#endif