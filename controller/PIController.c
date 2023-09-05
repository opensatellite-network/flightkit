/**
 * @file PIController.c
 * @author Krisna Pranav
 * @brief pic controller
 * @version 1.0
 * @date 2023-09-05
 * 
 * @copyright Copyright (c) 2023 opensatellite-network develoeprs, Krisna Pranav
 * 
 */

#include "PIController.h"
#include "controller/PIController.h"

/**
 * @param ctrl 
 * @param Kp 
 * @param Ki 
 * @param limMin 
 * @param limMax 
 */
void PI_Init(PIController *ctrl, float Kp, float Ki, float limMin, float limMax)
{
    ctrl->Kp = Kp;
    ctrl->Ki = Ki;
    ctrl->limMin = limMin;
    ctrl->limMax = limMax;
    ctrl->integrator = 0.0f;
    ctrl->prevError = 0.0f;
    ctrl->output = 0.0f;
    ctrl->limMinFF = 0.0f;
    ctrl->limMaxFF = 0.0f;
}

/**
 * @param ctrl 
 */
void PI_Reset(PIController *ctrl)
{
    ctrl->integrator = 0.0f;
    ctrl->prevError = 0.0f;
    ctrl->output = 0.0f;
}

/**
 * @param ctrl 
 * @param Kff 
 * @param limMinFF 
 * @param limMaxFF 
 */
void PI_SetFF(PIController *ctrl, float Kff, float limMinFF, float limMaxFF)
{
    ctrl->Kff = Kff;
    ctrl->limMinFF = limMaxFF;
    ctrl->limMaxFF = limMaxFF;
}

/**
 * @param ctrl 
 * @param setpoint 
 * @param measurement 
 * @param T 
 * @return float 
 */
float PI_Update(PIController *ctrl, float setpoint, float measurement, float T)
{
    float error = setpoint - measurement;
    float proportional = ctrl->Kp * error;

    float ff = ctrl->Kff * setpoint;

    if (ff > ctrl->limMaxFF) {
        ff = ctrl->limMaxFF;
    } else if (ff < ctrl->limMinFF) {
        ff = ctrl->limMinFF;
    }

    ctrl->integrator = ctrl->integrator + 0.5f * T * ctrl->Ki * (error + ctrl->prevError);

    return ctrl->output;
}