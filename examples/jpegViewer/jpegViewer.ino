/***********************************************************************
JPEG file Viewer for M5 Stack:
Please copy JPEG or BMP files to SD card in your M5 Stack.
    [Right] button to see next image.
    [Left] button to see previous image.
    [Center] button to stop/start automatic slide show.
************************************************************************
SDカードへ保存したJPEGファイルをM5 Stackの液晶画面へ表示します。
ボタン操作(右＝次、左＝前、中＝自動)で画像表示を制御することが出来ます。
※予めSDカードへJPEGファイルを保存してから、実行してください。
***********************************************************************/

#include "Adafruit_ILI9341.h"
#include <SPI.h>
#include <SD.h>
#include "JPEGDecoder.h"

#define BTN_A 39
#define BTN_B 38
#define BTN_C 37
#define SD_CS 4

#define SlideShowInterval 10

Adafruit_ILI9341 tft = Adafruit_ILI9341();
int autoSlideShow=1;

void setup(void) {
    Serial.begin(115200);
    pinMode(BTN_A,INPUT);
    pinMode(BTN_B,INPUT);
    pinMode(BTN_C,INPUT);
    tft.begin();
    tft.fillScreen(ILI9341_BLUE);

    tft.print("Initializing SD card...");
    if (!SD.begin(SD_CS)){
        tft.println("failed!");
        while(true) delay(100);
    }
    tft.println("OK!");
    jpegDrawSlideShowBegin(SD);
}

void loop() {
    if( !digitalRead(BTN_A) ){
        jpegDrawSlideShowPrev(SD);
    }
    if( !digitalRead(BTN_B) ){
        autoSlideShow = !autoSlideShow;
        if(autoSlideShow) tft.println("AUTO");
        else tft.println("STOP");
        delay(500);
    }
    if( !digitalRead(BTN_C) ){
        jpegDrawSlideShowNext(SD);
    }
    if(autoSlideShow && millis()%(SlideShowInterval*1000) == 0 ){
        jpegDrawSlideShowNext(SD);
        delay(1);
    }
}
