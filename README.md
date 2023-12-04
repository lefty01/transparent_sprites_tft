# transparent_sprites_tft
based on the excellent video tutorial and related code #VolosR/SpritesTuT by Volos Projects I compared tft_eSpi vs. LovyanGFX.

There were basically two things leading to this code (well besides the third reason to finally learn about sprites) a) convert volos code from tft_espi to lovyangfx and b) print some timing info about how long it takes for the sprite to move along a 240x135 tft screen.



## LovyanGFX Autodetect
```
#define LGFX_USE_V1
#define LGFX_AUTODETECT
#include <LovyanGFX.hpp>
```
It can automatically detect quite a number of boards/displays (e.g. TTGO-Display or TTGO-T4). So no need to make settings or changes to the library header files.


## code changes
In the TFT_eSPI example all sprites take the TFT_eSPI() object pointer as argument. Later in the code we can push sprite to another sprite.

```
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite rocketSprite = TFT_eSprite(&tft);  // moving rocket
TFT_eSprite bgSprite     = TFT_eSprite(&tft);  // background Sprite
TFT_eSprite txtSprite    = TFT_eSprite(&tft);  // text
TFT_eSprite txt2Sprite   = TFT_eSprite(&tft);  // text
```

In LGFX on the other hand onlye background sprite is using main LGFX object pointer, the other sprites take background sprite as their argument.
```
LGFX tft;
LGFX_Sprite bgSprite(&tft);
LGFX_Sprite rocketSprite(&bgSprite);
LGFX_Sprite txtSprite(&bgSprite);
LGFX_Sprite txt2Sprite(&bgSprite);
```


`createSprite`, `setSwapBytes`, and `pushImage` work the same using same arguments.


### drawSting
TFT_eSPI:
`txtSprite.drawString(String(x), 0, 0, 7);`
LGFX:
```
txtSprite.setTextFont(7);
txtSprite.drawString(String(x), 0, 0);
```

### pushing sprites to background
TFT_eSPI using pushToSprite:
```
  rocketSprite.pushToSprite(&bgSprite, x, 20, TFT_BLACK);
  txtSprite.pushToSprite(&bgSprite, 140, 80, TFT_BLACK);
  txt2Sprite.pushToSprite(&bgSprite, 15, 100, TFT_BLACK);
  bgSprite.pushSprite(0, 0);
```
LGFX only pushSprite, the layering defined at sprite construction above:
```
  rocketSprite.pushSprite(x, 20, TFT_BLACK);
  txtSprite.pushSprite(140, 80, TFT_BLACK);
  txt2Sprite.pushSprite(15, 100, TFT_BLACK);
  bgSprite.pushSprite(0, 0);
```



## numbers
the code prints number of milliseconds (millis) it takes between "wraping" of the moving sprite.

### TFT_eSPI
emacs: calc-grab-rectangle, calc-vector-mean
```
7874
7867
7870
7869
7874
7867
7870
7869
7874
7867
7870
7869
7874
7867
7870
7869
7874
```
2:  7870.23529412 mean

1:  2.7278519884  std deviation


### LovyanGFX
```
4293
4292
4292
4292
4292
4293
4292
4292
4292
4293
4292
4292
4292
4293
4292
4292
4292
```
1:  4292.23529412   mean

1:  0.437237316097  std dev.


![Photo](sprite.gif)

