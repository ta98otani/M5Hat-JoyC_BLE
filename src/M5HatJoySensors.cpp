#include "M5HatJoySensors.h"
#include "Hat_JoyC.h"
#include <Arduino.h>
#include <Wire.h>

JoyC joyc;

void setupFunctionM5HatJoySensors(uint32_T  LED_Color,int size_vector__1){

    joyc.begin();  // Initialize JoyC
    joyc.setLEDColor(LED_Color);
    Serial.begin(115200);

}

// X0 uint8 [1,1]
// Y0 uint8 [1,1]
// X1 uint8 [1,1]
// Y1 uint8 [1,1]
// Angle0 double [1,1]
// Angle1 double [1,1]
// Distance0 double [1,1]
// Distance1 double [1,1]
// Btn0 double [1,1]
// Btn1 double [1,1]
void stepFunctionM5HatJoySensors(uint8_T * X_left,int size_vector_1,uint8_T * Y_left,int size_vector_2,uint8_T * X_right,int size_vector_3,uint8_T * Y_right,int size_vector_4,uint16_T * Angle_left,int size_vector_5,uint16_T * Angle_right,int size_vector_6,uint16_T * Distance_left,int size_vector_7,uint16_T * Distance_right,int size_vector_8,boolean_T * Btn_left,int size_vector_9,boolean_T * Btn_right,int size_vector_10){
   
    joyc.update();

    *X_left         = joyc.x0;
    *Y_left         = joyc.y0;
    *X_right        = joyc.x1;
    *Y_right        = joyc.y1;
    *Angle_left     = joyc.angle0;
    *Angle_right    = joyc.angle1;
    *Distance_left  = joyc.distance0;
    *Distance_right = joyc.distance1;
    *Btn_left       = joyc.btn0;
    *Btn_right      = joyc.btn1;

    /*

char info[50];
    sprintf(info, "X0: %d Y0: %d", joyc.x0, joyc.y0);
    Serial.println(info);
    sprintf(info, "X1: %d Y1: %d", joyc.x1, joyc.y1);
    Serial.println(info);
    sprintf(info, "Angle0: %d Angle1: %d", joyc.angle0, joyc.angle1);
    Serial.println(info);
    sprintf(info, "D0: %d D1: %d", joyc.distance0, joyc.distance1);
    Serial.println(info);
    sprintf(info, "Btn0: %d Btn1: %d", joyc.btn0, joyc.btn1);
    Serial.println(info);
*/
    
}
