#ifndef ST7789_DIRECT_H
#define ST7789_DIRECT_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

// RGB565 color definitions
#define COLOR_BLACK   0x0000
#define COLOR_BLUE    0x001F
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_CYAN    0x07FF
#define COLOR_MAGENTA 0xF81F
#define COLOR_YELLOW  0xFFE0
#define COLOR_WHITE   0xFFFF

// AXP192 Power Management
#define AXP192_ADDR 0x34

class ST7789_Direct {
public:
    // Constructor
    ST7789_Direct(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t bl, 
                  uint8_t mosi, uint8_t sclk);
    
    // Initialization
    void begin();
    void setBacklight(bool on);
    void setBacklightLevel(uint8_t level);  // 0-255
    
    // Battery functions
    float getBatteryVoltage();      // Returns voltage in V (e.g., 3.7)
    float getBatteryCurrent();      // Returns current in mA
    int getBatteryLevel();          // Returns percentage 0-100
    bool isCharging();              // Returns true if charging
    
    // Basic display functions
    void fillScreen(uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    
    // Text display functions
    void setCursor(int16_t x, int16_t y);
    void setTextColor(uint16_t color);
    void setTextColor(uint16_t color, uint16_t bg);
    void setTextSize(uint8_t size);
    void print(const char* text);
    void print(int number);
    void print(float number, int decimals = 2);
    void println(const char* text);
    void println(int number);
    void println(float number, int decimals = 2);
    void println();
    
    // Fixed-width print functions (clears old digits)
    void printFixed(int number, uint8_t width);          // Right-aligned integer
    void printFixed(float number, uint8_t width, int decimals = 2);  // Right-aligned float
    
    // Fast batch rendering (advanced - for performance-critical code)
    void printFast(const char* text);  // Optimized rendering for single line
    
    // Screen dimensions
    int16_t width() { return _width; }
    int16_t height() { return _height; }

private:
    // Pin definitions
    uint8_t _cs, _dc, _rst, _bl, _mosi, _sclk;
    
    // Screen dimensions
    int16_t _width;
    int16_t _height;
    
    // Text cursor
    int16_t _cursor_x;
    int16_t _cursor_y;
    uint16_t _textcolor;
    uint16_t _textbgcolor;
    uint8_t _textsize;
    bool _wrap;
    
    // Offset values for M5StickC Plus
    uint8_t _xOffset;
    uint8_t _yOffset;
    
    // AXP192 functions
    void initAXP192();
    void writeAXP192(uint8_t reg, uint8_t data);
    uint8_t readAXP192(uint8_t reg);
    
    // Low-level functions
    void writeCommand(uint8_t cmd);
    void writeData(uint8_t data);
    void writeData16(uint16_t data);
    void writeDataBulk(uint16_t* data, uint32_t len);  // Bulk transfer
    void fillColor(uint16_t color, uint32_t len);      // Fast fill
    void setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void initLCD();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
};

#endif
