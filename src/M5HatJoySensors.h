/* Copyright 2023 The MathWorks, Inc. */
#ifndef EXAMPLE_H
#define EXAMPLE_H
#if !( defined(MATLAB_MEX_FILE) || defined(RSIM_PARAMETER_LOADING) ||  defined(RSIM_WITH_SL_SOLVER))
#include "rtwtypes.h"
#ifdef __cplusplus
extern "C" {
    #endif
    void setupFunctionM5HatJoySensors(uint32_T  LED_Color,int size_vector__1, boolean_T SensorDisplay, int size_vector__2);
    void stepFunctionM5HatJoySensors(uint8_T * X_left,int size_vector_1,uint8_T * Y_left,int size_vector_2,uint8_T * X_right,int size_vector_3,uint8_T * Y_right,int size_vector_4,uint16_T * Angle_left,int size_vector_5,uint16_T * Angle_right,int size_vector_6,uint16_T * Distance_left,int size_vector_7,uint16_T * Distance_right,int size_vector_8,boolean_T * Btn_left,int size_vector_9,boolean_T * Btn_right,int size_vector_10);
    #ifdef __cplusplus
}
#endif
#else
#define loop(void) (0)
#define setup(void) (0)
#endif
#endif
