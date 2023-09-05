/**
 * @file main.c
 * @author Krisna Pranav
 * @brief main
 * @version 1.0
 * @date 2023-09-05
 * 
 * @copyright Copyright (c) 2023 opensatellite-network develoeprs, Krisna Pranav
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "uavdatalink.h"

struct DataContainer_INS 
{
    float rollDeg;
    float pitchDeg;
    float yawDeg;
    float altitude;
} INSData;

int main() 
{
    INSData.rollDeg = 5.0;
    INSData.pitchDeg = -2.4;
    INSData.yawDeg = 69.69;
    INSData.altitude = 100.0;

    uint8_t UAVDataPacket[256];
    uint8_t UAVDataPacketLength;

    printf("Packet Length: ", UAVDataPacketLength);

    for (uint8_t n = 0; n < UAVDataPacketLength; n++) {
        printf("%i", UAVDataPacket[n]);
    }

    float extractedFloats[4];
    uint8_t nFloats = UAVDataLink_payloadToFloats();

    getchar();

    return 0;
}