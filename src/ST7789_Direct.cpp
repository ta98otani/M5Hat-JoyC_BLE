#include "ST7789_Direct.h"

// ST7789 commands
#define ST7789_NOP      0x00
#define ST7789_SWRESET  0x01
#define ST7789_SLPOUT   0x11
#define ST7789_NORON    0x13
#define ST7789_INVON    0x21
#define ST7789_DISPON   0x29
#define ST7789_CASET    0x2A
#define ST7789_RASET    0x2B
#define ST7789_RAMWR    0x2C
#define ST7789_MADCTL   0x36
#define ST7789_COLMOD   0x3A

// Simple 5x7 font
const uint8_t font5x7[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, // (space)
    0x00, 0x00, 0x5F, 0x00, 0x00, // !
    0x00, 0x07, 0x00, 0x07, 0x00, // "
    0x14, 0x7F, 0x14, 0x7F, 0x14, // #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
    0x23, 0x13, 0x08, 0x64, 0x62, // %
    0x36, 0x49, 0x56, 0x20, 0x50, // &
    0x00, 0x08, 0x07, 0x03, 0x00, // '
    0x00, 0x1C, 0x22, 0x41, 0x00, // (
    0x00, 0x41, 0x22, 0x1C, 0x00, // )
    0x2A, 0x1C, 0x7F, 0x1C, 0x2A, // *
    0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x80, 0x70, 0x30, 0x00, // ,
    0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x00, 0x60, 0x60, 0x00, // .
    0x20, 0x10, 0x08, 0x04, 0x02, // /
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x72, 0x49, 0x49, 0x49, 0x46, // 2
    0x21, 0x41, 0x49, 0x4D, 0x33, // 3
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x3C, 0x4A, 0x49, 0x49, 0x31, // 6
    0x41, 0x21, 0x11, 0x09, 0x07, // 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x46, 0x49, 0x49, 0x29, 0x1E, // 9
    0x00, 0x00, 0x14, 0x00, 0x00, // :
    0x00, 0x40, 0x34, 0x00, 0x00, // ;
    0x00, 0x08, 0x14, 0x22, 0x41, // <
    0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x00, 0x41, 0x22, 0x14, 0x08, // >
    0x02, 0x01, 0x59, 0x09, 0x06, // ?
    0x3E, 0x41, 0x5D, 0x59, 0x4E, // @
    0x7C, 0x12, 0x11, 0x12, 0x7C, // A
    0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x3E, 0x41, 0x41, 0x41, 0x22, // C
    0x7F, 0x41, 0x41, 0x41, 0x3E, // D
    0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x7F, 0x09, 0x09, 0x09, 0x01, // F
    0x3E, 0x41, 0x41, 0x51, 0x73, // G
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x20, 0x40, 0x41, 0x3F, 0x01, // J
    0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x7F, 0x02, 0x1C, 0x02, 0x7F, // M
    0x7F, 0x04, 0x08, 0x10, 0x7F, // N
    0x3E, 0x41, 0x41, 0x41, 0x3E, // O
    0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
    0x7F, 0x09, 0x19, 0x29, 0x46, // R
    0x26, 0x49, 0x49, 0x49, 0x32, // S
    0x03, 0x01, 0x7F, 0x01, 0x03, // T
    0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x3F, 0x40, 0x38, 0x40, 0x3F, // W
    0x63, 0x14, 0x08, 0x14, 0x63, // X
    0x03, 0x04, 0x78, 0x04, 0x03, // Y
    0x61, 0x59, 0x49, 0x4D, 0x43, // Z
    0x00, 0x7F, 0x41, 0x41, 0x41, // [
    0x02, 0x04, 0x08, 0x10, 0x20, // backslash
    0x00, 0x41, 0x41, 0x41, 0x7F, // ]
    0x04, 0x02, 0x01, 0x02, 0x04, // ^
    0x40, 0x40, 0x40, 0x40, 0x40, // _
    0x00, 0x03, 0x07, 0x08, 0x00, // `
    0x20, 0x54, 0x54, 0x78, 0x40, // a
    0x7F, 0x28, 0x44, 0x44, 0x38, // b
    0x38, 0x44, 0x44, 0x44, 0x28, // c
    0x38, 0x44, 0x44, 0x28, 0x7F, // d
    0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x00, 0x08, 0x7E, 0x09, 0x02, // f
    0x18, 0xA4, 0xA4, 0x9C, 0x78, // g
    0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x20, 0x40, 0x40, 0x3D, 0x00, // j
    0x7F, 0x10, 0x28, 0x44, 0x00, // k
    0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x7C, 0x04, 0x78, 0x04, 0x78, // m
    0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x38, 0x44, 0x44, 0x44, 0x38, // o
    0xFC, 0x18, 0x24, 0x24, 0x18, // p
    0x18, 0x24, 0x24, 0x18, 0xFC, // q
    0x7C, 0x08, 0x04, 0x04, 0x08, // r
    0x48, 0x54, 0x54, 0x54, 0x24, // s
    0x04, 0x04, 0x3F, 0x44, 0x24, // t
    0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x4C, 0x90, 0x90, 0x90, 0x7C, // y
    0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x00, 0x08, 0x36, 0x41, 0x00, // {
    0x00, 0x00, 0x77, 0x00, 0x00, // |
    0x00, 0x41, 0x36, 0x08, 0x00, // }
    0x02, 0x01, 0x02, 0x04, 0x02, // ~
};

ST7789_Direct::ST7789_Direct(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t bl,
                             uint8_t mosi, uint8_t sclk) {
    _cs = cs;
    _dc = dc;
    _rst = rst;
    _bl = bl;
    _mosi = mosi;
    _sclk = sclk;
    
    _width = 135;
    _height = 240;
    _xOffset = 52;
    _yOffset = 40;
    
    _cursor_x = 0;
    _cursor_y = 0;
    _textcolor = COLOR_WHITE;
    _textbgcolor = COLOR_BLACK;
    _textsize = 1;
    _wrap = true;
}

void ST7789_Direct::writeAXP192(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(AXP192_ADDR);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

uint8_t ST7789_Direct::readAXP192(uint8_t reg) {
    Wire.beginTransmission(AXP192_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(AXP192_ADDR, 1);
    return Wire.read();
}

void ST7789_Direct::initAXP192() {
    // Initialize I2C for AXP192
    Wire.begin(21, 22);  // SDA=21, SCL=22 for M5StickC Plus
    
    // LDO2: TFT backlight - 2.8V
    writeAXP192(0x28, 0xCC);  // Enable LDO2 & LDO3
    
    // GPIO0: LCD backlight control
    writeAXP192(0x90, 0x02);  // GPIO0 = LDO
    writeAXP192(0x91, 0xF0);  // GPIO0 voltage = 3.3V
    writeAXP192(0x92, 0x02);  // GPIO0 enable
    
    // DCDC1: Main 3.3V rail
    writeAXP192(0x26, 0x70);  // DCDC1 = 3.3V
    
    // DCDC3: LCD power - 3.0V
    writeAXP192(0x27, 0x64);  // DCDC3 = 3.0V
    
    // Enable DCDC1, DCDC3, LDO2, LDO3
    writeAXP192(0x12, 0x4D);
    
    // Backlight PWM mode
    writeAXP192(0x91, 0xF0);
    
    // Set backlight to maximum
    setBacklightLevel(255);
    
    delay(100);
}

void ST7789_Direct::setBacklightLevel(uint8_t level) {
    // AXP192 backlight control (0-255)
    uint8_t brightness = level >> 4;  // Convert to 0-15
    if (brightness > 12) brightness = 12;  // Limit to 12 max
    writeAXP192(0x28, 0xC0 | brightness);
}

float ST7789_Direct::getBatteryVoltage() {
    // Read battery voltage from AXP192 (registers 0x78-0x79)
    uint16_t raw = (readAXP192(0x78) << 4) | (readAXP192(0x79) & 0x0F);
    // Conversion: raw * 1.1mV
    return raw * 1.1 / 1000.0;  // Convert to volts
}

float ST7789_Direct::getBatteryCurrent() {
    // Read battery current (positive = charging, negative = discharging)
    // Charge current: registers 0x7A-0x7B
    // Discharge current: registers 0x7C-0x7D
    
    uint16_t charge = (readAXP192(0x7A) << 5) | (readAXP192(0x7B) & 0x1F);
    uint16_t discharge = (readAXP192(0x7C) << 5) | (readAXP192(0x7D) & 0x1F);
    
    // Conversion: raw * 0.5mA
    float chargeCurrent = charge * 0.5;
    float dischargeCurrent = discharge * 0.5;
    
    // Return net current (positive when charging)
    return chargeCurrent - dischargeCurrent;
}

int ST7789_Direct::getBatteryLevel() {
    // Calculate battery percentage based on voltage
    // LiPo battery: 4.2V (100%) to 3.0V (0%)
    float voltage = getBatteryVoltage();
    
    if (voltage >= 4.2) return 100;
    if (voltage <= 3.0) return 0;
    
    // Linear approximation
    int percentage = (int)((voltage - 3.0) / (4.2 - 3.0) * 100.0);
    
    // Clamp to 0-100
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;
    
    return percentage;
}

bool ST7789_Direct::isCharging() {
    // Read power status register (0x00)
    // Bit 2: VBUS present (charging)
    uint8_t status = readAXP192(0x00);
    return (status & 0x04) != 0;  // Check bit 2
}

void ST7789_Direct::begin() {
    // Initialize AXP192 power management FIRST
    initAXP192();
    
    // Initialize pins
    pinMode(_cs, OUTPUT);
    pinMode(_dc, OUTPUT);
    pinMode(_rst, OUTPUT);
    
    digitalWrite(_cs, HIGH);
    digitalWrite(_dc, HIGH);
    
    // Initialize SPI
    SPI.begin(_sclk, -1, _mosi, -1);
    SPI.setFrequency(40000000);  // 40MHz - faster!
    
    // Initialize LCD
    initLCD();
    
    delay(50);
}

void ST7789_Direct::setBacklight(bool on) {
    setBacklightLevel(on ? 255 : 0);
}

void ST7789_Direct::writeCommand(uint8_t cmd) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    SPI.transfer(cmd);
    digitalWrite(_cs, HIGH);
}

void ST7789_Direct::writeData(uint8_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    SPI.transfer(data);
    digitalWrite(_cs, HIGH);
}

void ST7789_Direct::writeData16(uint16_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    SPI.transfer(data >> 8);
    SPI.transfer(data & 0xFF);
    digitalWrite(_cs, HIGH);
}

// Bulk write function - keeps CS low for entire transfer
void ST7789_Direct::writeDataBulk(uint16_t* data, uint32_t len) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    
    // Use 8-bit array for faster transfer
    uint8_t buffer[64];  // Small buffer for chunked transfers
    uint32_t remaining = len;
    uint32_t offset = 0;
    
    while (remaining > 0) {
        uint32_t chunk = (remaining > 32) ? 32 : remaining;  // 32 pixels at a time
        
        // Convert 16-bit pixels to 8-bit bytes
        for (uint32_t i = 0; i < chunk; i++) {
            buffer[i * 2] = data[offset + i] >> 8;
            buffer[i * 2 + 1] = data[offset + i] & 0xFF;
        }
        
        // Use optimized writeBytes
        SPI.writeBytes(buffer, chunk * 2);
        
        offset += chunk;
        remaining -= chunk;
    }
    
    digitalWrite(_cs, HIGH);
}

// Even faster - write same color multiple times
void ST7789_Direct::fillColor(uint16_t color, uint32_t len) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    
    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;
    
    // Create a buffer with repeated color for faster transfer
    uint8_t buffer[128];  // 64 pixels worth
    for (int i = 0; i < 128; i += 2) {
        buffer[i] = hi;
        buffer[i + 1] = lo;
    }
    
    // Send in large chunks
    uint32_t remaining = len;
    while (remaining > 0) {
        uint32_t chunk = (remaining > 64) ? 64 : remaining;
        SPI.writeBytes(buffer, chunk * 2);
        remaining -= chunk;
    }
    
    digitalWrite(_cs, HIGH);
}

void ST7789_Direct::initLCD() {
    // Hardware reset
    digitalWrite(_rst, HIGH);
    delay(5);
    digitalWrite(_rst, LOW);
    delay(20);
    digitalWrite(_rst, HIGH);
    delay(150);
    
    writeCommand(ST7789_SWRESET);
    delay(150);
    
    writeCommand(ST7789_SLPOUT);
    delay(120);
    
    writeCommand(ST7789_COLMOD);
    writeData(0x55);
    delay(10);
    
    writeCommand(ST7789_MADCTL);
    writeData(0x00);
    
    writeCommand(ST7789_INVON);
    delay(10);
    
    writeCommand(ST7789_NORON);
    delay(10);
    
    writeCommand(ST7789_DISPON);
    delay(20);
}

void ST7789_Direct::setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    // Column address set
    writeCommand(ST7789_CASET);
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    SPI.transfer((x0 + _xOffset) >> 8);
    SPI.transfer((x0 + _xOffset) & 0xFF);
    SPI.transfer((x1 + _xOffset) >> 8);
    SPI.transfer((x1 + _xOffset) & 0xFF);
    digitalWrite(_cs, HIGH);
    
    // Row address set
    writeCommand(ST7789_RASET);
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    SPI.transfer((y0 + _yOffset) >> 8);
    SPI.transfer((y0 + _yOffset) & 0xFF);
    SPI.transfer((y1 + _yOffset) >> 8);
    SPI.transfer((y1 + _yOffset) & 0xFF);
    digitalWrite(_cs, HIGH);
    
    // Write to RAM
    writeCommand(ST7789_RAMWR);
}

void ST7789_Direct::fillScreen(uint16_t color) {
    setWindow(0, 0, _width - 1, _height - 1);
    
    // Use fast bulk fill instead of byte-by-byte
    fillColor(color, (uint32_t)_width * _height);
}

void ST7789_Direct::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    // Clip to screen bounds
    if (x >= _width || y >= _height) return;
    if (x + w > _width) w = _width - x;
    if (y + h > _height) h = _height - y;
    if (w <= 0 || h <= 0) return;
    
    setWindow(x, y, x + w - 1, y + h - 1);
    fillColor(color, (uint32_t)w * h);
}

void ST7789_Direct::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x >= _width || y < 0 || y >= _height) return;
    
    setWindow(x, y, x, y);
    writeData16(color);
}

void ST7789_Direct::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
    if (c < 32 || c > 126) c = '?';
    
    // For size 1, use ultra-optimized single-window approach
    if (size == 1) {
        // Create buffer in row-major order for entire character (5x8 = 40 pixels)
        uint16_t buffer[40];
        
        // ST7789 expects pixels in row-major order (left-to-right, top-to-bottom)
        // Font data is column-major, so we need to reorganize
        for (int8_t row = 0; row < 8; row++) {
            for (int8_t col = 0; col < 5; col++) {
                uint8_t line = pgm_read_byte(&font5x7[(c - 32) * 5 + col]);
                buffer[row * 5 + col] = (line & (1 << row)) ? color : bg;
            }
        }
        
        // Set window ONCE for entire character
        setWindow(x, y, x + 4, y + 7);
        
        // Write entire character in ONE bulk transfer
        writeDataBulk(buffer, 40);
        
    } else {
        // For larger sizes, draw scaled character
        // Create buffer for scaled character
        uint16_t w = 5 * size;
        uint16_t h = 8 * size;
        uint16_t totalPixels = w * h;
        
        // Allocate buffer (stack limit check)
        if (totalPixels <= 320) {  // Reasonable limit for stack
            uint16_t buffer[320];  // Max for size 2 (10x16 = 160 pixels)
            
            // Fill buffer in row-major order
            for (int8_t row = 0; row < 8; row++) {
                for (int8_t col = 0; col < 5; col++) {
                    uint8_t line = pgm_read_byte(&font5x7[(c - 32) * 5 + col]);
                    uint16_t pixelColor = (line & (1 << row)) ? color : bg;
                    
                    // Scale pixel to size x size block
                    for (uint8_t sy = 0; sy < size; sy++) {
                        for (uint8_t sx = 0; sx < size; sx++) {
                            uint16_t idx = (row * size + sy) * w + (col * size + sx);
                            buffer[idx] = pixelColor;
                        }
                    }
                }
            }
            
            // Draw entire scaled character in one operation
            setWindow(x, y, x + w - 1, y + h - 1);
            writeDataBulk(buffer, totalPixels);
            
        } else {
            // Fallback for very large sizes - draw pixel by pixel
            for (int8_t i = 0; i < 5; i++) {
                uint8_t line = pgm_read_byte(&font5x7[(c - 32) * 5 + i]);
                for (int8_t j = 0; j < 8; j++, line >>= 1) {
                    uint16_t pixelColor = (line & 1) ? color : bg;
                    for (uint8_t a = 0; a < size; a++) {
                        for (uint8_t b = 0; b < size; b++) {
                            drawPixel(x + i * size + a, y + j * size + b, pixelColor);
                        }
                    }
                }
            }
        }
    }
}

void ST7789_Direct::setCursor(int16_t x, int16_t y) {
    _cursor_x = x;
    _cursor_y = y;
}

void ST7789_Direct::setTextColor(uint16_t color) {
    _textcolor = color;
    _textbgcolor = color;
}

void ST7789_Direct::setTextColor(uint16_t color, uint16_t bg) {
    _textcolor = color;
    _textbgcolor = bg;
}

void ST7789_Direct::setTextSize(uint8_t size) {
    _textsize = (size > 0) ? size : 1;
}

void ST7789_Direct::print(const char* text) {
    // Quick optimization for size 1 text - try to batch render
    if (_textsize == 1) {
        const char* start = text;
        int charCount = 0;
        
        // Count consecutive printable characters (no newlines)
        while (*text && *text != '\n' && *text != '\r') {
            charCount++;
            text++;
            
            // Check if we'd wrap
            int16_t nextX = _cursor_x + charCount * 6;
            if (_wrap && nextX > (_width - 6)) {
                charCount--;  // Don't include character that would wrap
                break;
            }
        }
        
        // If we have consecutive chars, batch render them
        if (charCount > 0) {
            // Use optimized batch rendering
            if (charCount <= 20) {
                // Create buffer for batch
                uint16_t totalWidth = charCount * 6;
                uint16_t totalPixels = totalWidth * 8;
                uint16_t buffer[960];  // Max 20 chars
                
                // Fill buffer with all characters
                for (int charIdx = 0; charIdx < charCount; charIdx++) {
                    unsigned char c = start[charIdx];
                    if (c < 32 || c > 126) c = '?';
                    
                    int baseX = charIdx * 6;
                    
                    // Render character into buffer
                    for (int8_t row = 0; row < 8; row++) {
                        for (int8_t col = 0; col < 5; col++) {
                            uint8_t line = pgm_read_byte(&font5x7[(c - 32) * 5 + col]);
                            uint16_t pixelColor = (line & (1 << row)) ? _textcolor : _textbgcolor;
                            buffer[row * totalWidth + baseX + col] = pixelColor;
                        }
                        // Add 1 pixel space after character
                        buffer[row * totalWidth + baseX + 5] = _textbgcolor;
                    }
                }
                
                // Draw entire batch in ONE operation
                setWindow(_cursor_x, _cursor_y, _cursor_x + totalWidth - 1, _cursor_y + 7);
                writeDataBulk(buffer, totalPixels);
                
                // Update cursor
                _cursor_x += totalWidth;
                
                // Continue with rest of string if any
                if (*text) {
                    print(text);  // Recursive call for remainder
                }
                return;
                
            } else {
                // Too many chars for buffer, draw in chunks of 20
                char chunk[21];
                strncpy(chunk, start, 20);
                chunk[20] = '\0';
                print(chunk);
                print(start + 20);  // Recursive for rest
                return;
            }
        }
    }
    
    // Fallback: original character-by-character rendering
    // Used for: size > 1, newlines, or very long strings
    while (*text) {
        if (*text == '\n') {
            _cursor_y += _textsize * 8;
            _cursor_x = 0;
        } else if (*text == '\r') {
            // Skip
        } else {
            drawChar(_cursor_x, _cursor_y, *text, _textcolor, _textbgcolor, _textsize);
            _cursor_x += _textsize * 6;
            if (_wrap && (_cursor_x > (_width - _textsize * 6))) {
                _cursor_y += _textsize * 8;
                _cursor_x = 0;
            }
        }
        text++;
    }
}

void ST7789_Direct::print(int number) {
    char buffer[12];
    itoa(number, buffer, 10);
    print(buffer);
}

void ST7789_Direct::print(float number, int decimals) {
    char buffer[32];
    // dtostrf(value, min_width, num_decimals, buffer)
    // Use -1 for min_width to left-justify
    dtostrf(number, 1, decimals, buffer);
    
    // Remove leading spaces that dtostrf might add
    char* ptr = buffer;
    while (*ptr == ' ') ptr++;
    
    print(ptr);
}

void ST7789_Direct::println(const char* text) {
    print(text);
    _cursor_y += _textsize * 8;
    _cursor_x = 0;
}

void ST7789_Direct::println(int number) {
    print(number);
    _cursor_y += _textsize * 8;
    _cursor_x = 0;
}

void ST7789_Direct::println(float number, int decimals) {
    print(number, decimals);
    _cursor_y += _textsize * 8;
    _cursor_x = 0;
}

void ST7789_Direct::println() {
    _cursor_y += _textsize * 8;
    _cursor_x = 0;
}

void ST7789_Direct::printFixed(int number, uint8_t width) {
    char buffer[12];
    itoa(number, buffer, 10);
    
    int len = strlen(buffer);
    
    // Build complete string with leading spaces
    char output[32];
    int idx = 0;
    
    // Add leading spaces to reach desired width
    for (int i = len; i < width; i++) {
        output[idx++] = ' ';
    }
    
    // Add the number
    strcpy(&output[idx], buffer);
    
    // Use optimized print (will auto-batch)
    print(output);
}

void ST7789_Direct::printFixed(float number, uint8_t width, int decimals) {
    char buffer[32];
    dtostrf(number, 1, decimals, buffer);
    
    // Remove leading spaces
    char* ptr = buffer;
    while (*ptr == ' ') ptr++;
    
    int len = strlen(ptr);
    
    // Build complete string with leading spaces
    char output[32];
    int idx = 0;
    
    // Add leading spaces to reach desired width
    for (int i = len; i < width; i++) {
        output[idx++] = ' ';
    }
    
    // Add the number
    strcpy(&output[idx], ptr);
    
    // Use optimized print (will auto-batch)
    print(output);
}

void ST7789_Direct::printFast(const char* text) {
    // Fast rendering for size 1 text only
    if (_textsize != 1) {
        print(text);  // Fall back to normal print
        return;
    }
    
    int len = strlen(text);
    if (len == 0) return;
    
    // Limit to reasonable length to avoid stack overflow
    if (len > 20) {
        print(text);  // Fall back for very long strings
        return;
    }
    
    // Calculate total buffer size
    uint16_t totalWidth = len * 6;  // Each char is 6 pixels wide (5 + 1 space)
    uint16_t totalPixels = totalWidth * 8;  // 8 pixels tall
    
    // Allocate buffer
    uint16_t buffer[960];  // Max 20 chars * 6 wide * 8 tall = 960 pixels
    
    // Fill buffer with all characters
    for (int charIdx = 0; charIdx < len; charIdx++) {
        unsigned char c = text[charIdx];
        if (c < 32 || c > 126) c = '?';
        
        int baseX = charIdx * 6;
        
        // Render character into buffer
        for (int8_t row = 0; row < 8; row++) {
            for (int8_t col = 0; col < 5; col++) {
                uint8_t line = pgm_read_byte(&font5x7[(c - 32) * 5 + col]);
                uint16_t pixelColor = (line & (1 << row)) ? _textcolor : _textbgcolor;
                buffer[row * totalWidth + baseX + col] = pixelColor;
            }
            // Add 1 pixel space after character
            buffer[row * totalWidth + baseX + 5] = _textbgcolor;
        }
    }
    
    // Draw entire string in ONE operation
    setWindow(_cursor_x, _cursor_y, _cursor_x + totalWidth - 1, _cursor_y + 7);
    writeDataBulk(buffer, totalPixels);
    
    // Update cursor
    _cursor_x += totalWidth;
}
