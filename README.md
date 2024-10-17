# esp32-tft2.8-touch ILI9341
esp32-tft2.8-touch - some codes

# Necessary Info !
## DONT FORGET TO MAKE SURE this line `#define ILI9341_DRIVER` in User_Setup.h is uncommented
- exactly be sure this line should looks like this down in User_setup.h : 
```
#define ILI9341_DRIVER       // Generic driver for common displays
```
- and uncomment this also
```
// ###### EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP32 SETUP   ######

// For ESP32 Dev board (only tested with ILI9341 display)
// The hardware SPI can be mapped to any pins

------------> (UNCOMENT HERE DOWN  THIS LINES) <------------
//#define TFT_MISO 19
//#define TFT_MOSI 23
//#define TFT_SCLK 18
//#define TFT_CS   15  // Chip select control pin
//#define TFT_DC    2  // Data Command control pin
//#define TFT_RST   4  // Reset pin (could connect to RST pin)

#define TOUCH_CS 21     // Chip select pin (T_CS) of touch screen
```

# Conection
## TFT -> esp32
- VCC -> 3.3V
- GND -> GND
- CS -> D15
- RST -> D
- DC -> D2
- MOSI -> D23
- LED -> 3.3V
- SCK -> D18
- MISO -> 19
## For TOUCH Function
- T_CLK -> 
- T_CS -> 
- T_DIN -> 
- T_DO -> 
- T_IRQ ->


# for Rpi4 TFT Display connection
| TFT Module | ESP32 Board |
|------------|-------------|
| TFT 5V     | 5V          |
| TFT GND    | GND         |
| TFT MISO   | Pin 19      |
| TFT MOSI   | Pin 23      |
| TFT SCK    | Pin 18      |
| TFT CS     | Pin 16      |
| TFT DC     | Pin 2       |
| TFT RST    | Pin 4       |
| TFT T_CS   | Pin 21      |

### SD Card Module

| SD Card module | ESP32 Board          |
|----------------|----------------------|
| SD 3v3         | 3V3                  |
| SD GND         | GND                  |
| SD CS          | Pin 15               |
| SD SCK (clk)   | Pin 18 (same as TFT) |
| SD MOSI        | Pin 23 (same as TFT) |
| SD MISO        | Pin 19 (same as TFT) |
