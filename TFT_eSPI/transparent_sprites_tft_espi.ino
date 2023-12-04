//#include <SPI.h>
#include <TFT_eSPI.h>

#include "rocket.h"



TFT_eSPI tft = TFT_eSPI();
TFT_eSprite rocketSprite = TFT_eSprite(&tft);  // moving rocket
TFT_eSprite bgSprite     = TFT_eSprite(&tft);  // background Sprite
TFT_eSprite txtSprite    = TFT_eSprite(&tft);  // text
TFT_eSprite txt2Sprite   = TFT_eSprite(&tft);  // text


int dispWidth;
int dispHeight;

int x = 20;
int angle = 0;
unsigned long prevMillis = 0;
unsigned long millisPerMove;

void setup() {
  Serial.begin(115200);
  delay(20);

  // put your setup code here, to run once:
  tft.init();
  tft.setRotation(1);
  dispWidth  = tft.width();
  dispHeight = tft.height();
  Serial.print("width:  "); Serial.println(dispWidth);
  Serial.print("height: "); Serial.println(dispHeight);
  //tft.setSwapBytes(true);
  // ttgo display resolution is 135*240

  txtSprite.createSprite(100, 60);
  txtSprite.setTextColor(TFT_WHITE, TFT_BLACK);
  txt2Sprite.createSprite(100, 60);
  txt2Sprite.setTextColor(TFT_WHITE, TFT_BLACK);

  bgSprite.createSprite(240, 135);

  rocketSprite.createSprite(90, 90);
  rocketSprite.setSwapBytes(true);

}

void loop() {

  bgSprite.fillSprite(TFT_PURPLE);

  txtSprite.fillSprite(TFT_BLACK);
  txtSprite.drawString(String(x), 0, 0, 7);

  txt2Sprite.fillSprite(TFT_BLACK);
  txt2Sprite.drawString(String(millisPerMove), 0, 0, 4);

  rocketSprite.pushImage(0, 0, 90, 90, rocket);
  rocketSprite.pushToSprite(&bgSprite, x, 20, TFT_BLACK);
  txtSprite.pushToSprite(&bgSprite, 140, 80, TFT_BLACK);
  txt2Sprite.pushToSprite(&bgSprite, 15, 100, TFT_BLACK);


  bgSprite.pushSprite(0, 0);

  x++;

  //if (x > 240) x =- 100;
  if (x > 240) {
    x = -90;

    millisPerMove = millis() - prevMillis;
    prevMillis = millis();
    Serial.println(millisPerMove);
  }
  //tft.drawString(String(x), 140, 80, 7);
  //delay(10);
}
