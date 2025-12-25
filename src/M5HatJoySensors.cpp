#include "M5HatJoySensors.h"
#include "Hat_JoyC.h"
#include <Arduino.h>
#include <Wire.h>
#include "ST7789_Direct.h"

// M5StickC Plus LCD pins
#define TFT_MOSI    15
#define TFT_SCLK    13
#define TFT_CS      5
#define TFT_DC      23
#define TFT_RST     18
#define TFT_BL      10

JoyC joyc;
// Create LCD object
ST7789_Direct lcd(TFT_CS, TFT_DC, TFT_RST, TFT_BL, TFT_MOSI, TFT_SCLK);
boolean SensorDisplayEnable;

void setupFunctionM5HatJoySensors(uint32_T  LED_Color,int size_vector__1, boolean_T SensorDisplay, int size_vector__2){

    lcd.begin();   // Initializing LCD
    joyc.begin();  // Initialize JoyC
    joyc.setLEDColor(LED_Color);
    lcd.fillScreen(COLOR_BLACK);

    // Display Some Text in LCD
    lcd.setTextSize(2);
    lcd.setTextColor(COLOR_GREEN, COLOR_BLACK);
    lcd.setCursor(10, 10);
    lcd.println("JoyC BLE");

    SensorDisplayEnable = SensorDisplay;

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

   float voltage = lcd.getBatteryVoltage();   

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

    if (SensorDisplayEnable) {
        // Set Font Size
        lcd.setTextSize(2);

        // Display Battery  (Of M5Stick)
        lcd.setCursor(10, 30);
        lcd.printFast("Batt:");
        lcd.printFixed(voltage, 4,1);  // Display Voltage
        lcd.printFast("V");

        // X0
        lcd.setCursor(10, 100);
        lcd.setTextColor(COLOR_YELLOW, COLOR_BLACK);
        lcd.printFast("L-X: ");
        lcd.setTextColor(COLOR_WHITE, COLOR_BLACK);
        lcd.printFixed(*X_left, 3);

        // X1
        lcd.setCursor(10, 120);
        lcd.setTextColor(COLOR_YELLOW, COLOR_BLACK);
        lcd.printFast("L-Y: ");
        lcd.setTextColor(COLOR_WHITE, COLOR_BLACK);
        lcd.printFixed(*Y_left, 3);

        // X1
        lcd.setCursor(10, 140);
        lcd.setTextColor(COLOR_YELLOW, COLOR_BLACK);
        lcd.printFast("R-X: ");
        lcd.setTextColor(COLOR_WHITE, COLOR_BLACK);
        lcd.printFixed(*X_right, 3);

        // Y1
        lcd.setCursor(10, 160);
        lcd.setTextColor(COLOR_YELLOW, COLOR_BLACK);
        lcd.printFast("R-Y: ");
        lcd.setTextColor(COLOR_WHITE, COLOR_BLACK);
        lcd.printFixed(*Y_right, 3);

        // // Angle_L
        // lcd.setCursor(10, 140);
        // lcd.setTextColor(COLOR_YELLOW, COLOR_BLACK);
        // lcd.print("Lang:");
        // lcd.setTextColor(COLOR_WHITE, COLOR_BLACK);
        // lcd.print(*Angle_left, 0);
        //
        // // Angle_R
        // lcd.setCursor(10, 160);
        // lcd.setTextColor(COLOR_YELLOW, COLOR_BLACK);
        // lcd.print("Rang:");
        // lcd.setTextColor(COLOR_WHITE, COLOR_BLACK);
        // lcd.print(*Angle_right, 0);
        //
        // // Distance L
        // lcd.setCursor(10, 180);
        // lcd.setTextColor(COLOR_YELLOW, COLOR_BLACK);
        // lcd.print("Ldist:");
        // lcd.setTextColor(COLOR_WHITE, COLOR_BLACK);
        // lcd.print(*Distance_left, 0);
        //
        // // Distance R
        // lcd.setCursor(10, 200);
        // lcd.setTextColor(COLOR_YELLOW, COLOR_BLACK);
        // lcd.print("Rdist:");
        // lcd.setTextColor(COLOR_WHITE, COLOR_BLACK);
        // lcd.print(*Distance_right, 0);

    }

}
