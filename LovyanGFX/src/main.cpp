// based on examples / tutorial by Volos Projects ()

#define LGFX_USE_V1
#define LGFX_AUTODETECT

#include <LovyanGFX.hpp>


//#include "binaryttf.h"
//#include "OpenFontRender.h"
// #include "biomuell_90x50.h"
// #include "papiermuell_90x50.h"
// #include "restmuell_90x50.h"

// #include <Ticker.h>
// // 1 second tickers
// #define TICKER_INTERVALL 1000
// // min intervall 10 minutes, in the loop we some random time on top
// #define MIN_INTERVALL 5 * 60
// // Create a ticker
// jsc::Ticker ticker_1sec(TICKER_INTERVALL);

//WiFiClientSecure client;

#include "rocket.h"


LGFX tft;
LGFX_Sprite bgSprite(&tft);
LGFX_Sprite rocketSprite(&bgSprite);
LGFX_Sprite txtSprite(&bgSprite);
LGFX_Sprite txt2Sprite(&bgSprite);


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

  // Serial.print("Connecting to ");
  // Serial.println(WIFI_SSID);
  // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  //   // timeout check ...
  // }
  // Serial.println("");
  // Serial.println("WiFi connected.");


  tft.startWrite();  // ?
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

  //  txtSprite.setTextFont(4);           // フォント種類を変更(時計盤の文字用)
  //  txtSprite.setTextDatum(lgfx::middle_center);


  rocketSprite.pushSprite(x, 20, TFT_BLACK);
  txtSprite.pushSprite(140, 80, TFT_BLACK);
  txt2Sprite.pushSprite(15, 100, TFT_BLACK);
  bgSprite.pushSprite(0, 0);


  x++;
  if (x > 240) {
    x = -90;
    millisPerMove = millis() - prevMillis;
    prevMillis = millis();
    Serial.println(millisPerMove);
  }

  tft.display();  // ?
}
