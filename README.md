# M5Hat-JoyC_BLE Simulink Support Block

## Overview

### 
This is a code forked from M5Hat-JoyC to enable BLE transmission to a Robot.

This project include Simulink model to call M5Hat-JoyC library code to access JoyC I2C data. 
The skelton was generated Arduino IO Device Builder, which is part of Simulink Arduino Support Package (see "Software Requirement" section below)

https://www.mathworks.com/help/simulink/arduino-io-device-builder.html

Most of the C++ code to access SPI display and initializing AXP192 power management (ST7789_Direct.cpp and ST7789_Direct.h) was created using AI Coding tools.


## Required Software
- Tested against MATLAB version R2024b and Arduino Hardware Support Package (Free Download)
- https://jp.mathworks.com/matlabcentral/fileexchange/40312-simulink-support-package-for-arduino-hardware
- (It is best to use Add-on manager of MATLAB to install the addons)

## Getting Started
1. Open M5HatJoyC_BLE24b.xls
2. Change hardware settings (COM Ports appropriately)
  <img width="1294" height="743" alt="image" src="https://github.com/user-attachments/assets/16dc4cc1-7266-44d8-a8d2-094b575273d5" />

4. Build and Run
<img width="911" height="132" alt="image" src="https://github.com/user-attachments/assets/0f61b810-6d63-4152-afcd-72cac02b6e28" />

   

## Related Link
- HatJoy I2C library code (Hat_JoyC.cpp and Hat_JoyC.h) was largely leveraged from 
https://github.com/m5stack/M5Hat-JoyC
- [Document & Datasheet - M5Hat-JoyC](https://docs.m5stack.com/en/hat/hat-joyc)

## Disclaimer
Personal project - Use at your own risk. This code is provided as-is, without any warranty.
