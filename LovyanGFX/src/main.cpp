// based on examples / tutorial by Volos Projects ()

#define LGFX_USE_V1
#define LGFX_AUTODETECT

#include <LovyanGFX.hpp>

#include "rocket.h"


LGFX tft;
// LGFX_Sprite bgSprite(&tft);
// LGFX_Sprite rocketSprite(&bgSprite);
// LGFX_Sprite txtSprite(&bgSprite);
// LGFX_Sprite txt2Sprite(&bgSprite);
LGFX_Sprite bgSprite;
LGFX_Sprite rocketSprite;
LGFX_Sprite txtSprite;
LGFX_Sprite txt2Sprite;


//static auto transpalette = 0;
int dispWidth;
int dispHeight;

int x = 20;
int angle = 0;
unsigned long prevMillis = 0;
unsigned long millisPerMove;

void setup() {
  Serial.begin(115200);
  delay(20);

  tft.init();
  tft.setBrightness(200);


  tft.setRotation(1);  // vert (240x320)
  //tft.setColorDepth(24);
  dispWidth  = tft.width();
  dispHeight = tft.height();
  Serial.print("width:  "); Serial.println(dispWidth);
  Serial.print("height: "); Serial.println(dispHeight);

  // T4 has 240x320
  // width:  240
  // height: 320
  //sprite.createSprite(dispWidth, 20);
  txtSprite.createSprite(100, 60);
  txtSprite.setTextColor(TFT_WHITE, TFT_BLACK);
  txt2Sprite.createSprite(100, 60);
  txt2Sprite.setTextColor(TFT_WHITE, TFT_BLACK);

  //bgSprite.setColorDepth(lgfx::palette_8bit);
  bgSprite.createSprite(dispWidth, dispHeight);

  rocketSprite.createSprite(90, 90);
  rocketSprite.setSwapBytes(true);
  rocketSprite.pushImage(0, 0, 90, 90, rocket);

}

uint n = 0;
void loop() {
  bgSprite.fillSprite(TFT_PURPLE);
  //bgSprite.fillSprite(TFT_ORANGE);


  txtSprite.fillSprite(TFT_BLACK);
  txtSprite.setTextFont(7);
  txtSprite.drawString(String(x), 0, 0);

  txt2Sprite.fillSprite(TFT_BLACK);
  txt2Sprite.setTextFont(4);
  txt2Sprite.drawString(String(millisPerMove), 0, 0);



  rocketSprite.pushSprite(&bgSprite, x, 20, TFT_BLACK);
  txtSprite.pushSprite(&bgSprite, 140, 80, TFT_BLACK);
  txt2Sprite.pushSprite(&bgSprite, 15, 100, TFT_BLACK);
  bgSprite.pushSprite(&tft, 0, 0);


  x++;
  if (x > 240) {
    x = -90;
    millisPerMove = millis() - prevMillis;
    prevMillis = millis();
    Serial.println(millisPerMove);
  }

  tft.display();
}
