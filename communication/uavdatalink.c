/**
 * @file uavdatalink.c
 * @author Krisna Pranav
 * @brief uav data link
 * @version 1.0
 * @date 2023-09-05
 * 
 * @copyright Copyright (c) 2023 opensatellite-network develoeprs, Krisna Pranav
 * 
 */

#include "uavdatalink.h"

uint8_t UAVDataLink_pack(const uint8_t IDA, const uint8_t IDB, const uint8_t PAYLOADLENGTH, const uint8_t *PAYLOAD, uint8_t *byteStreamOut)
{
    static uint8_t SEQUENCE = 1;

    uint8_t n;

    uint8_t rawDataLength = 5 + PAYLOADLENGTH;
    uint8_t rawData[rawDataLength];

    rawData[0] = SEQUENCE;
    rawData[1] = IDA;
    rawData[2] = IDB;
    rawData[3] = PAYLOADLENGTH;

    for (n = 0; n < PAYLOADLENGTH; n++) {
        rawData[4 + n] = PAYLOAD[n];
    }

    uint8_t cs = 0;

    for (n = 0; n < PAYLOADLENGTH; n++) {
        cs ^= PAYLOAD[n];
    }

    rawData[rawDataLength - 1] = cs;

    uint8_t encodePacketLength = UAVDataLink_encodeCOBS(rawData, rawDataLength, byteStreamOut);

    if (SEQUENCE == 255) {
        SEQUENCE = 1;
    } else {
        SEQUENCE++;
    }

    return encodePacketLength;      
}