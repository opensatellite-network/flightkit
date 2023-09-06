/**
 * @file GPSParser.h
 * @author Krisna Pranav
 * @brief GPS Parser
 * @version 1.0
 * @date 2023-09-06
 * 
 * @copyright Copyright (c) 2023 opensatellite-network develoeprs, Krisna Pranav
 * 
 */

#ifndef GPS_PARSER_H
#define GPS_PARSER_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define GPS_USER_GGA

typedef enum
{
    NONE,
    GGA,
    RMC,
    VTG
} NMEASentenceType;

typedef struct 
{
    float latitude_dec;
    float longitude_dec;
    float altitude_m;
    float groundspeed_mps;
    float course_deg;
    uint8_t fix;
} GPSData;

/**
 * @param gpsData 
 */
void GPSNMEAParser_Init(GPSData *gpsData);

/**
 * @param gpsData 
 */
void GPSNMEAParser_ExtractRMC(GPSData *gpsData);

/**
 * @param gpsData 
 * @param c 
 */
void GPSNMEAParser_Freed(GPSData *gpsData, char c);
#endif