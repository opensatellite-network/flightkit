/**
 * @file IIRFirstOrder.h
 * @author Krisna Pranav
 * @brief iir first order
 * @version 1.0
 * @date 2023-09-06
 * 
 * @copyright Copyright (c) 2023 opensatellite-network develoeprs, Krisna Pranav
 * 
 */

#ifndef FILTER_IIR_FIRST_ORDER_H
#define FILTER_IIR_FIRST_ORDER_H

typedef struct
{
    float alpha;
    float out;
} IIRFirstOrder;

/**
 * @param filt 
 * @param alpha 
 */
void IIRFirstOrder_Init(IIRFirstOrder *filt, float alpha)
{
    filt->alpha = alpha;
    filt->out = 0.0f;
}

#endif