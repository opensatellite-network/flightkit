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

#include <stdint.h>

/**
 * @param IDA 
 * @param IDB 
 * @param PAYLOADLENGTH 
 * @param PAYLOAD 
 * @param byteStreamOut 
 * @return uint8_t 
 */
uint8_t UAVDataLink_pack(const uint8_t IDA, const uint8_t IDB, const uint8_t PAYLOADLENGTH, const uint8_t *PAYLOAD, uint8_t *byteStreamOut);

/**
 * @param receivedPacket 
 * @param receivedPacketLength 
 * @param packetHeader 
 * @param payload 
 * @return uint8_t 
 */
uint8_t UAVDataLink_unpack(uint8_t *receivedPacket, uint8_t receivedPacketLength, uint8_t *packetHeader, uint8_t *payload);

/**
 * @param dataIn 
 * @param dataInLength 
 * @param dataOut 
 * @return uint8_t 
 */
uint8_t UAVDataLink_encodeCOBS(const uint8_t *dataIn, const uint8_t dataInLength, uint8_t *dataOut);

/**
 * @param dataIn 
 * @param dataInLength 
 * @param dataOut 
 * @return uint8_t 
 */
uint8_t UAVDataLink_decodeCOBS(const uint8_t *dataIn, const uint8_t dataInLength, uint8_t *dataOut);

/**
 * @param payload 
 * @param payloadLength 
 * @param extractedFloats 
 * @return uint8_t 
 */
uint8_t UAVDataLink_payloadToFloats(const uint8_t *payload, const uint8_t payloadLength, float *extractedFloats);

/**
 * @param arr 
 * @param arrLength 
 * @return uint8_t 
 */
uint8_t UAVDataLink_checksum(const uint8_t *arr, const uint8_t arrLength);

typedef union FloatConverterUnion 
{
    float val;
    uint8_t bytes[4];
} FloatConverter;

/**
 * @param IDA 
 * @param IDB 
 * @param PAYLOADLENGTH 
 * @param PAYLOAD 
 * @param byteStreamOut 
 * @return uint8_t 
 */
uint8_t UAVDataLink_pack(const uint8_t IDA, const uint8_t IDB, const uint8_t PAYLOADLENGTH, const uint8_t *PAYLOAD, uint8_t *byteStreamOut);

/**
 * @param receivedPacket 
 * @param receivedPacketLength 
 * @param packetHeader 
 * @param payload 
 * @return uint8_t 
 */
uint8_t UAVDataLink_unpack(uint8_t *receivedPacket, uint8_t receivedPacketLength, uint8_t *packetHeader, uint8_t *payload);

/**
 * @param payload 
 * @param payloadLength 
 * @param extractedFloats 
 * @return uint8_t 
 */
uint8_t UAVDataLink_payloadToFloats(const uint8_t *payload, const uint8_t payloadLength, float *extractedFloats);

/**
 * @param dataIn 
 * @param dataInLength 
 * @param dataOut 
 * @return uint8_t 
 */
uint8_t UAVDataLink_encodeCOBS(const uint8_t *dataIn, const uint8_t dataInLength, uint8_t *dataOut);

/**
 * @param dataIn 
 * @param dataInLength 
 * @param dataOut 
 * @return uint8_t 
 */
uint8_t UAVDataLink_decodeCOBS(const uint8_t *dataIn, const uint8_t dataInLength, uint8_t *dataOut);

/**
 * @param arr 
 * @param arrLength 
 * @return uint8_t 
 */
uint8_t UAVDataLink_checksum(const uint8_t *arr, const uint8_t arrLength);

#endif