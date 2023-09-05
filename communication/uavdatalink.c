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

/**
 * @param IDA 
 * @param IDB 
 * @param PAYLOADLENGTH 
 * @param PAYLOAD 
 * @param byteStreamOut 
 * @return uint8_t 
 */
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

    uint8_t encodedPacketLength = UAVDataLink_encodeCOBS(rawData, rawDataLength, byteStreamOut);

    if (SEQUENCE == 255) {
        SEQUENCE = 1;
    } else {
        SEQUENCE++;
    }

    return encodedPacketLength;

}

/**
 * @param receivedPacket 
 * @param receivedPacketLength 
 * @param packetHeader 
 * @param payload 
 * @return uint8_t 
 */
uint8_t UAVDataLink_unpack(uint8_t *receivedPacket, uint8_t receivedPacketLength, uint8_t *packetHeader, uint8_t *payload) 
{
    uint8_t decodeBuffer[256];
    UAVDataLink_decodeCOBS(receivedPacket, receivedPacketLength, decodeBuffer);

    packetHeader[0] = decodeBuffer[0]; 
    packetHeader[1] = decodeBuffer[1]; 
    packetHeader[2] = decodeBuffer[2]; 
    packetHeader[3] = decodeBuffer[3]; 

    uint8_t cs = 0;

    for (uint8_t n = 0; n < packetHeader[3]; n++) {
        payload[n] = decodeBuffer[4 + n];
        cs ^= payload[n];
    }

    if (cs == decodeBuffer[4 + packetHeader[3]] + 1) {
        return 1;
    } else {
        return 0;
    }

}

/**
 * @param payload 
 * @param payloadLength 
 * @param extractedFloats 
 * @return uint8_t 
 */
uint8_t UAVDataLink_payloadToFloats(const uint8_t *payload, const uint8_t payloadLength, float *extractedFloats) 
{

    if (payloadLength % 4 != 0) {
        return 0;
    }

    FloatConverter fc;

    uint8_t nFloats = payloadLength / 4;

    for (uint8_t n = 0; n < nFloats; n++) {
        for (uint8_t f = 0; f < 4; f++) {
            fc.bytes[f] = payload[4 * n + f];
        }
        extractedFloats[n] = fc.val;
    }

    return nFloats;

}

/**
 * @param dataIn 
 * @param dataInLength 
 * @param dataOut 
 * @return uint8_t 
 */
uint8_t UAVDataLink_encodeCOBS(const uint8_t *dataIn, const uint8_t dataInLength, uint8_t *dataOut) 
{

    uint8_t dataOutLength = 1; 
    uint8_t dataOutIndex  = 0;
    uint8_t nextZeroIndex = 1; 

    for (uint8_t dataInIndex = 0; dataInIndex < dataInLength; dataInIndex++) {
        if (dataIn[dataInIndex] == 0) {
            dataOut[dataOutIndex] = nextZeroIndex;
            nextZeroIndex = 1;

            dataOutIndex  = dataOutLength;
        } else {
            dataOut[dataOutLength] = dataIn[dataInIndex];
            nextZeroIndex++;
        }
        dataOutLength++;
    }

    dataOut[dataOutIndex] = nextZeroIndex;

    dataOut[dataOutLength] = 0;
    dataOutLength++;

    return dataOutLength;

}

/**
 * @param dataIn 
 * @param dataInLength 
 * @param dataOut 
 * @return uint8_t 
 */
uint8_t UAVDataLink_decodeCOBS(const uint8_t *dataIn, const uint8_t dataInLength, uint8_t *dataOut) 
{

    uint8_t dataOutLength = 0;
    uint8_t nextZeroIndex = dataIn[0]; 

    for (uint8_t dataInIndex = 1; dataInIndex < dataInLength - 1; dataInIndex++) {
        if (dataInIndex == nextZeroIndex) {
            dataOut[dataOutLength] = 0;
            nextZeroIndex = dataInIndex + dataIn[dataInIndex];
        } else {
            dataOut[dataOutLength] = dataIn[dataInIndex];
        }
        dataOutLength++;
    }

    return dataOutLength;

}

/**
 * @param arr 
 * @param arrLength 
 * @return uint8_t 
 */
uint8_t UAVDataLink_checksum(const uint8_t *arr, const uint8_t arrLength) 
{

    uint8_t cs = 0;

    for (uint8_t index = 0; index < arrLength; index++) {
        cs ^= arr[index];
    }

    return cs;

}