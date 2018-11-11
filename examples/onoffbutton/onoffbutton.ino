/***********************************************************************
example: buttons on M5 Stack
************************************************************************
M5 Stack 上のボタン操作のデモ用サンプルです
***********************************************************************/

#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>

#define FRAME_X 60
#define FRAME_Y 180
#define FRAME_W 100
#define FRAME_H 50

#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W/2)
#define REDBUTTON_H FRAME_H

#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y
#define GREENBUTTON_W (FRAME_W/2)
#define GREENBUTTON_H FRAME_H

#define M5_STACK_BTN_A 39
#define M5_STACK_BTN_B 38
#define M5_STACK_BTN_C 37

Adafruit_ILI9341 tft = Adafruit_ILI9341();

void drawFrame()
{
  tft.drawRect(FRAME_X, FRAME_Y, FRAME_W, FRAME_H, ILI9341_BLACK);
}

void redBtn()
{ 
  tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_RED);
  tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_BLUE);
  drawFrame();
  tft.setCursor(GREENBUTTON_X + 6 , GREENBUTTON_Y + (GREENBUTTON_H/2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("ON");
}

void greenBtn()
{
  tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_GREEN);
  tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLUE);
  drawFrame();
  tft.setCursor(REDBUTTON_X + 6 , REDBUTTON_Y + (REDBUTTON_H/2));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("OFF");
}

void resetBtn()
{
  tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_BLUE);
  tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLUE);
  drawFrame();
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(REDBUTTON_X + 16 , REDBUTTON_Y + (REDBUTTON_H/2));
  tft.println("Reset");
}

void setup(void)
{
  Serial.begin(115200);
  tft.begin();
  pinMode(M5_STACK_BTN_A,INPUT);
  pinMode(M5_STACK_BTN_B,INPUT);
  pinMode(M5_STACK_BTN_C,INPUT);

  tft.fillScreen(ILI9341_BLUE);
  redBtn();
}

void loop()
{
    if( digitalRead(M5_STACK_BTN_A) == LOW ) {
          Serial.println("Red btn hit"); 
          redBtn();
          delay(100);
    }
    if( digitalRead(M5_STACK_BTN_B) == LOW ) {
          Serial.println("Green btn hit"); 
          greenBtn();
          delay(100);
    }
    if( digitalRead(M5_STACK_BTN_C) == LOW ) {
          Serial.println("Reset"); 
          resetBtn();
          delay(100);
    }
}

/***********************************************************************
本ソースリストは2018/11/6に下記からダウンロードしたものを、
国野亘が m5 stack用に改変したものです。

	https://github.com/adafruit/Adafruit_ILI9341

2018/11/6 国野 亘
***********************************************************************/

//This example implements a simple sliding On/Off button. The example
// demonstrates drawing and touch operations.
//
//Thanks to Adafruit forums member Asteroid for the original sketch!
//
