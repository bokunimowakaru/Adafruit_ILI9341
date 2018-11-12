/***********************************************************************
BMP data Viewer for M5 Stack:
The bitmap data is included in "dragon.h"
************************************************************************
ビットマップデータをM5 Stackの液晶画面へ表示します。
***********************************************************************/

#include "SPI.h"
#include <Adafruit_ILI9341.h>
#include "dragon.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(14,27);

void setup() {
  tft.begin();
}

void loop(void) {
  for(uint8_t r=0; r<4; r++) {
    tft.setRotation(r);
    tft.fillScreen(ILI9341_BLACK);
    for(uint8_t j=0; j<20; j++) {
      tft.drawRGBBitmap(
        random(-DRAGON_WIDTH , tft.width()),
        random(-DRAGON_HEIGHT, tft.height()),
#if defined(__AVR__) || defined(ESP8266)
        dragonBitmap,
#else
        // Some non-AVR MCU's have a "flat" memory model and don't
        // distinguish between flash and RAM addresses.  In this case,
        // the RAM-resident-optimized drawRGBBitmap in the ILI9341
        // library can be invoked by forcibly type-converting the
        // PROGMEM bitmap pointer to a non-const uint16_t *.
        (uint16_t *)dragonBitmap,
#endif
        DRAGON_WIDTH, DRAGON_HEIGHT);
      delay(1); // Allow ESP8266 to handle watchdog & WiFi stuff
    }
    delay(3000);
  }
}

/***********************************************************************
本ソースリストは2018/11/6に下記からダウンロードしたものを、
国野亘が m5 stack用に改変したものです。

	https://github.com/adafruit/Adafruit_ILI9341

2018/11/6 国野 亘
***********************************************************************/

// ILI9341 example with embedded color bitmaps in sketch.
// WILL NOT FIT ON ARDUINO UNO OR OTHER AVR BOARDS;
// uses large bitmap image stored in array!

// Options for converting images to the format used here include:
//   http://www.rinkydinkelectronics.com/t_imageconverter565.php
// or
//  GIMP (https://www.gimp.org/) as follows:
//    1. File -> Export As
//    2. In Export Image dialog, use 'C source code (*.c)' as filetype.
//    3. Press export to get the export options dialog.
//    4. Type the desired variable name into the 'prefixed name' box.
//    5. Uncheck 'GLIB types (guint8*)'
//    6. Check 'Save as RGB565 (16-bit)'
//    7. Press export to save your image.
//  Assuming 'image_name' was typed in the 'prefixed name' box of step 4,
//  you can have to include the c file, then using the image can be done with:
//    tft.drawRGBBitmap(0, 0, image_name.pixel_data, image_name.width, image_name.height);
//  See also https://forum.pjrc.com/threads/35575-Export-for-ILI9341_t3-with-GIMP

