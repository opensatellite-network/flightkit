/**
 * @file uavdatalink.h
 * @author Krisna PRanav
 * @brief uav data linker
 * @version 1.0
 * @date 2023-09-05
 * 
 * @copyright Copyright (c) 2023 opensatellite-network develoeprs, Krisna Pranav
 * 
 */

#ifndef _COMMUNICATION_UAV_DATA_LINK_H
#define _COMMUNICATION_UAV_DATA_LINK_H

typedef union FloatConverterUnion 
{
    float val;
    uint8_t bytes[4];
} FloatConverter;

/**
 * @param arr 
 * @param arrLength 
 * @return uint8_t 
 */
uint8_t UAVDataLink_checksum(const uint8_t *arr, const uint8_t arrLength);

#endif