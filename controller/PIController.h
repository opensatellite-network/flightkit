/**
 * @file PIController.h
 * @author Krisna Pranav
 * @brief pic controller
 * @version 1.0
 * @date 2023-09-05
 * 
 * @copyright Copyright (c) 2023 opensatellite-network develoeprs, Krisna Pranav
 * 
 */

#ifndef CONTROLLER_PI_CONTROLLER_H
#define CONTROLLER_PI_CONTROLLER_H

typedef struct
{
    float Kp;
    float Ki;
    float Kff;
    float limMin;
    float limMax;
    float limMinFF;
    float limMaxFF;
    float prevError;
} PIController;

/**
 * @param ctrl 
 * @param Kp 
 * @param Ki 
 * @param linMin 
 * @param linMax 
 */
void PI_Init(PIController *ctrl, float Kp, float Ki, float linMin, float linMax);

/**
 * @param ctrl 
 */
void PI_Reset(PIController *ctrl);

/**
 * @param ctrl 
 * @param Kff 
 * @param limMinFF 
 * @param linMaxFF 
 */
void PI_SetFF(PIController *ctrl, float Kff, float limMinFF, float linMaxFF);

#endif 