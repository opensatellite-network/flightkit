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

#define GPS_USE_GGA

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
	float groundSpeed_mps;
	float course_deg;
	float magVariation_deg;
	float meanSeaLevel_m;

	uint8_t fix;
	uint8_t fixQuality;
	uint8_t numSatellites;
	uint8_t latitudeNS;
	uint8_t longitudeEW;
	
	NMEASentenceType curSentence;

	uint8_t readingHeader;
	uint8_t readingSentenceData;

	char headerBuf[6];

	uint8_t headerBufIndex;

	char segmentBuf[16];

	uint8_t segmentBufIndex;
	uint8_t segmentCount;
} GPSData;


/**
 * @param gpsData 
 */
void GPSNMEAParser_Init(GPSData *gpsData);

/**
 * @param gpsData 
 */
void GPSNMEAParser_ExtractGGA(GPSData *gpsData);

/**
 * @param gpsData 
 */
void GPSNMEAParser_ExtractRMC(GPSData *gpsData);

/**
 * @param gpsData 
 * @param c 
 */
void GPSNMEAParser_Feed(GPSData *gpsData, char c);

#endif