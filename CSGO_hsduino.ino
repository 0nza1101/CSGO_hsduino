#include <Adafruit_GFX.h>    // Core graphics library
//#include <./Fonts/FreeSerif9pt7b.h>
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>


#define LCD_CS A3 
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define YP A1
#define XM A2 
#define YM 7  
#define XP 6   

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 0
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF

#define GAME_VER   "         1.0"

/*GAME VARIABLES*/
boolean isPlaying = false;
short maxScore = 0;
unsigned int score = 0;

static const unsigned char PROGMEM TERRORIST[]{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x27,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x37,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x21,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x60,0xff,0xef,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xff,0xaf,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xeb,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xfd,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xf8,0x40,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x7f,0x8f,0xf8,0x40,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x70,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x70,0x20,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x70,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x5,0x8,0x0,0x0,0x1f,0x90,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0x90,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc0,0x0,0x3f,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc0,0x0,0x3f,0xb0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x3d,0x88,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x7d,0x88,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x79,0xc8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf8,0x1,0xfb,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0x1,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0xf,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0x7,0xdf,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0xf,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfe,0xf,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xef,0xff,0x60,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0x70,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x4,0x0,0x0,0x7,0xff,0xdf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x1,0xff,0xdb,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x7f,0xeb,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x83,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x7,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0x7,0xfe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0x7,0xfe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x77,0x87,0xfe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xf6,0xf,0xff,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x76,0x1f,0xff,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x36,0x1f,0xff,0xf8,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x30,0x0,0x0,0x70,0x3f,0xff,0xff,0xe0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x78,0x0,0x0,0xc0,0x3f,0xff,0xff,0xf0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x70,0x0,0x3,0x80,0x3f,0xff,0xff,0xfc,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x3,0x0,0x7f,0xff,0xff,0xff,0x80,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xc0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xec,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xf0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xec,0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xec,0x0,0x0,0x1,0xff,0xff,0xff,0xdf,0xff,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1c,0xec,0x0,0x0,0x3,0xff,0xbf,0xff,0xf,0xff,0xc0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xe4,0x0,0x0,0xf,0xff,0x1f,0xef,0x1f,0xff,0xf0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xef,0x0,0x0,0xf,0xfe,0x1f,0x3,0xff,0xff,0xf8,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xfd,0x0,0x0,0xf,0xfe,0x3f,0xfc,0xff,0xff,0xfc,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xec,0x0,0x0,0x3f,0xfe,0x7f,0xff,0xff,0xff,0xfe,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xfd,0xed,0x40,0x0,0x7f,0xfc,0xff,0xff,0xff,0xff,0xff,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xfb,0xed,0xc0,0x0,0x7f,0xfc,0xff,0xff,0xff,0xff,0xff,0x80,
0x0,0x0,0x0,0x0,0x0,0x0,0x1e,0x23,0xe7,0xe0,0x1,0xff,0xfc,0xff,0xff,0xff,0xff,0xff,0xc0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1c,0x3,0xe3,0x88,0x3,0xff,0xf9,0xff,0xff,0xff,0xff,0xff,0xe0,
0x0,0x0,0x0,0x0,0x0,0x0,0x18,0x7,0xe3,0xe2,0x3,0xff,0xf9,0xff,0xff,0xff,0xff,0xff,0xf0,
0x0,0x0,0x0,0x0,0x0,0x0,0x60,0x7,0xf8,0xfb,0xbf,0xff,0xf8,0xff,0xff,0xff,0xff,0xff,0xf0,
0x0,0x0,0x0,0x0,0x0,0x0,0x60,0x7,0xfc,0x3f,0xff,0xff,0x78,0xff,0xff,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x0,0x60,0x7,0xfc,0x3f,0xff,0xfe,0x78,0x7f,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x60,0x7,0xee,0x3b,0xff,0xfe,0xf8,0x5f,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x40,0x7,0xff,0x8f,0xff,0xff,0xf0,0x3f,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x40,0x5,0xff,0xdf,0xff,0xff,0xf0,0xd,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0xc0,0xf,0xdf,0xfb,0xff,0xff,0xf0,0x9,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x3f,0xff,0xff,0xfd,0xe0,0x9,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x1f,0xf7,0xff,0xf9,0xe0,0x1,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xf3,0xff,0xf9,0xc0,0x0,0x3f,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xc3,0x9f,0xf3,0xc0,0x0,0x3f,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xf1,0x1f,0xe1,0xc0,0x0,0x3f,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xe0,0x1f,0xf1,0xc0,0x0,0x7f,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xe1,0xf0,0x5f,0xaf,0xc0,0x0,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xc0,0x0,0x1f,0xe7,0xc0,0x0,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xe0,0x0,0x3f,0xa7,0xc0,0x1,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xe0,0x2,0x7f,0x87,0x80,0x1,0xf8,0x7f,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xf0,0x3c,0xff,0x7,0x80,0x1,0xf8,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xe0,0xc,0xff,0x1f,0x0,0x0,0x0,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3e,0xfc,0x79,0xfe,0xe,0x0,0x0,0x3,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xfc,0x3b,0xfc,0xe,0x0,0x0,0x3,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x10,0x0,0x3f,0xf8,0x77,0xfc,0xe,0x0,0x0,0x7,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xef,0xfc,0x1c,0x0,0x0,0xf,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xfe,0xcf,0xfc,0x3c,0x0,0x0,0x1f,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xfe,0x8f,0xf8,0x38,0x0,0x0,0x3f,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xbf,0xfa,0x70,0x0,0x0,0x3f,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xbf,0x3f,0xf0,0x70,0x0,0x0,0x7b,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xbe,0x7f,0xe4,0x70,0x0,0x0,0x73,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xbd,0x7f,0xe4,0x70,0x0,0x0,0xc7,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x80,0x0,0xf,0xdc,0xff,0xe9,0xe0,0x0,0x0,0x83,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x80,0x0,0x7,0xd9,0xff,0xe0,0xe0,0x0,0x0,0x7,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xfb,0xff,0xc1,0xc0,0x0,0x0,0x0,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x7,0xef,0xff,0x91,0x80,0x0,0x0,0x0,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x1,0xf8,0x7,0x83,0xef,0xff,0x1,0x80,0x0,0x0,0x0,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0xf8,0x3f,0xc3,0xef,0xff,0x83,0x80,0x0,0x0,0x0,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x1,0xfe,0x1,0xc7,0xff,0xc3,0x86,0x80,0x0,0x1,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x3,0xfc,0x1,0x8f,0xff,0xc7,0x81,0x0,0x0,0x3,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x3,0xf,0xf0,0x0,0xf,0xfe,0x87,0x0,0x0,0x0,0x7,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x2,0xf,0x0,0x18,0x1f,0xfc,0x1e,0x1,0xc0,0x0,0x3f,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x2,0x0,0x2e,0x0,0x38,0x9f,0xf9,0x1e,0x3f,0xc0,0x0,0x3f,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x4,0x0,0x7e,0x0,0xc0,0x17,0xf1,0x1c,0x3e,0x0,0x0,0x37,0xff,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x0,0x3,0x0,0x3b,0xe6,0x3c,0x3,0x80,0x80,0x70,0x7f,0xff,0xff,0xf8,
0x0,0x0,0x0,0x80,0x0,0x0,0x6,0x0,0x3b,0xce,0x7c,0x3,0xc1,0x80,0x40,0x7f,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x0,0x1c,0x0,0x7d,0xec,0xfc,0x7,0xf0,0x0,0xc0,0x7f,0xff,0xff,0xf8,
0x0,0x0,0x0,0x0,0x0,0x0,0xe0,0x0,0x3c,0xf0,0xf8,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xf8,
0x0,0x0,0x20,0x40,0x0,0x1,0xe0,0x0,0x3c,0x71,0xf0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xf8,
0x0,0x0,0x40,0x23,0x80,0x1,0x80,0x0,0x1e,0x7f,0xe0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xfc,
0x0,0x0,0x80,0x18,0x10,0x0,0x0,0x0,0x1f,0xbf,0xe0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xfc,
0x0,0x0,0xe,0x18,0xf,0x0,0x0,0x0,0x1f,0x83,0xc0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xfc,
0x0,0x0,0xf,0x9,0xf,0xc0,0x0,0x0,0x1f,0xc1,0x80,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xfc,
0x0,0x0,0x7c,0x0,0x1f,0xe2,0x0,0x0,0xd,0xf0,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xfc,
0x0,0xf,0xfc,0x0,0x1f,0xf4,0x0,0x0,0xd,0xfc,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xfc,
0x0,0x1f,0xf0,0x0,0x1f,0xf8,0x0,0x0,0xc,0x7e,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xfc,
0x0,0xff,0xe0,0x0,0x1f,0xf8,0x0,0x20,0xc,0x7e,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xfc,
0x0,0x3f,0xe6,0x0,0x1,0xfe,0x0,0x30,0xc,0x7c,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xfc,
0x0,0x3f,0xf8,0x0,0x1,0xff,0x0,0x30,0xc,0x78,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xfc,
0x4,0x7f,0xd0,0x0,0x1,0xff,0x0,0x3c,0xe,0x78,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xfc,
0x0,0x7f,0x80,0x0,0x0,0xff,0xc0,0x7,0xe,0x70,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xfc,
0x0,0x7f,0x0,0x0,0x0,0xff,0xe0,0x7,0xf,0x70,0x0,0x0,0x0,0x0,0x0,0x3,0x7f,0xff,0xfc,
0x0,0x7e,0x0,0x1,0x80,0xff,0xe0,0x7,0x8f,0x30,0x0,0x0,0x38,0x0,0x0,0x0,0x3f,0xff,0xfc,
0x0,0x7c,0x0,0x0,0x0,0x7,0xc0,0x3,0xcf,0x80,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xfc,
0x0,0xfc,0x0,0x0,0x0,0x1,0xc0,0x3,0xcf,0x86,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xfc,
0x0,0xf8,0x0,0x0,0x0,0x0,0x80,0x3,0xcf,0x84,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xfc,
0x0,0xf0,0xd,0x0,0x0,0x0,0x0,0x3,0x80,0x80,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xfc,
0x0,0xe0,0x1d,0x0,0x0,0x0,0x0,0x0,0x2,0xc0,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xfc,
0x0,0xe0,0x7e,0x0,0x0,0x0,0x0,0x0,0x2,0xf0,0x0,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xfc,
0x1,0xe1,0xfc,0x0,0x0,0x0,0x0,0x0,0x9c,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,
0x3,0xc1,0xf8,0x0,0x0,0x0,0x0,0x30,0x88,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,
0x7,0xc1,0xf0,0x0,0x0,0x0,0x0,0x0,0x84,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,
0x3,0x81,0xc0,0x0,0x0,0x0,0x0,0x0,0x8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,
0x1,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x90,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,
0x0,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,
0xff,0x60,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc
};

static const unsigned char PROGMEM HEAD[]{
  0x0,0x0,0x0,0x7f,0xfe,0x0,0x0,0x0,0x0,
0x0,0x0,0xf,0xff,0xff,0x80,0x0,0x0,0x0,
0x0,0x0,0x2,0x7f,0xff,0xe0,0x0,0x0,0x0,
0x0,0x0,0x2,0xff,0xff,0xf8,0x0,0x0,0x0,
0x0,0x0,0x0,0x1f,0xff,0xfe,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7f,0xff,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x27,0xff,0x80,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0xff,0xc0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0xff,0xe0,0x0,0x0,
0x0,0x0,0x0,0x0,0x13,0xff,0xf0,0x0,0x0,
0x0,0x0,0x0,0x0,0x17,0xff,0xf8,0x0,0x0,
0x0,0x0,0x0,0x0,0xf,0xff,0xfc,0x0,0x0,
0x0,0x0,0x0,0x3,0x2f,0xff,0xfe,0x0,0x0,
0x0,0x0,0x0,0xf,0x7f,0xff,0xff,0x0,0x0,
0x0,0x0,0x1,0xff,0xff,0xff,0xff,0x80,0x0,
0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xc0,0x0,
0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xc0,0x0,
0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0x2f,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,
0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,
0x0,0xf,0xff,0xff,0xf1,0xff,0xff,0xf8,0x0,
0x0,0xb,0xff,0xff,0xf,0xf3,0xff,0xfc,0x0,
0x10,0x0,0x3f,0xfe,0xf8,0xf,0xff,0xfc,0x0,
0x8,0x10,0x3f,0xff,0xc0,0x7f,0x4f,0xfc,0x0,
0xf,0xff,0xff,0xff,0x0,0x7f,0x3f,0xfe,0x0,
0xc,0x0,0x0,0x4,0x0,0xf,0xbf,0xf6,0x0,
0x8,0x0,0x1,0xfc,0x0,0x1,0xbf,0xf7,0x0,
0x0,0x0,0x1,0xfc,0x0,0x0,0x3f,0xff,0x0,
0x0,0x0,0x0,0xfc,0x0,0x0,0x3f,0xff,0x0,
0x0,0x0,0x0,0xfc,0x0,0x0,0x3f,0xf3,0x80,
0x0,0x0,0x0,0xfe,0x0,0x0,0x7f,0xf1,0x80,
0x0,0x0,0x0,0xfe,0x0,0x0,0x7f,0xff,0x80,
0x0,0x0,0x1,0x7f,0x0,0x0,0x7f,0xff,0x80,
0x0,0x0,0x1,0x7f,0x0,0x0,0xff,0xff,0x0,
0x0,0x0,0x1,0x7f,0xc0,0x3,0xff,0xff,0x0,
0x4,0x0,0x2,0x7f,0xf0,0x7,0xff,0xff,0x0,
0x2,0x0,0x4,0x7f,0xfc,0xff,0xff,0xff,0x0,
0x2,0x0,0x8,0x7f,0xff,0xff,0xff,0xfe,0x0,
0x1,0x0,0x10,0x7f,0xf1,0xff,0xff,0xfc,0x0,
0x1,0xc0,0x60,0x7f,0xf1,0xff,0xff,0xf8,0x0,
0x1,0xff,0xe0,0x7f,0xf0,0xff,0xff,0xf0,0x0,
0x0,0x7f,0xe0,0x7f,0xff,0xff,0xff,0xc0,0x0,
0x40,0x3f,0xe0,0x3f,0x3f,0xff,0xff,0xc0,0x0,
0x40,0x3f,0xf0,0x0,0x7f,0xff,0xff,0x80,0x0,
0x20,0x1f,0xf0,0x0,0xff,0xff,0xff,0x80,0x0,
0x10,0xf,0xf0,0x0,0xff,0xff,0xff,0x0,0x0,
0x0,0xf,0xf0,0x0,0x7f,0xff,0xff,0x0,0x0,
0x0,0x3,0xc0,0x0,0x7,0xff,0xff,0x0,0x0,
0x0,0x1,0x80,0x0,0x1,0xff,0xfe,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7f,0xfe,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7f,0xf8,0x0,0x0,
0x0,0x0,0x0,0x0,0xf,0xff,0xf0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7f,0xff,0xf0,0x0,0x0,
0x0,0x0,0x0,0x3,0xff,0xff,0xe0,0x0,0x0,
0x0,0x0,0x0,0x7,0xff,0xff,0xe0,0x0,0x0,
0x0,0x0,0x1e,0x0,0x7,0xff,0xc0,0x0,0x0,
0x0,0x0,0xf,0x0,0x7,0xff,0xc0,0x0,0x0,
0x0,0x0,0xd,0x0,0xf,0xff,0x80,0x0,0x0,
0x0,0x0,0x0,0x0,0x1f,0xfe,0x0,0x0,0x0,
0x0,0x0,0x3,0x40,0x3f,0xf0,0x0,0x0,0x0,
0x0,0x0,0x1,0xc0,0x7f,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x78,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

void setup() {
   tft.reset();
   uint16_t identifier = tft.readID();
   tft.begin(identifier);
   tft.setRotation(2);
   tft.fillScreen(BLACK);
  // tft.setFont(&FreeSerif9pt7b);
  Serial.begin(9600);

}

void loop() {
  mainMenu();
}

void mainMenu(void){ 
  tft.drawBitmap(40, 155, TERRORIST, 150, 147, WHITE);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(40, 40);
  tft.print("CS:GO HSduino\n");tft.print(GAME_VER);//Title  

  tft.setTextColor(WHITE);
  tft.drawRect(40, 100, 155, 50, WHITE);//Play
  tft.setCursor(90, 120);
  tft.print("Play");
  
  /*tft.drawRect(40, 190, 155, 50, WHITE);//About
  tft.setCursor(90, 210);
  tft.print("About");*/

  tft.setCursor(35, tft.height()-10);
  tft.setTextSize(1);
  tft.print("DoneGames Open Source project");
  
  //Touch screen declaration
  TSPoint p = ts.getPoint();
  digitalWrite(13, HIGH);
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
  {
    p.x = tft.width()-(map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
    p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
    //Touch screen detection
    if (p.x < 140){
      if( p.y  > 140) {
        play();
      }
    }
  }
}

void play(){
  tft.fillScreen(BLACK);//Clear screen
  tft.setRotation(3);
  isPlaying = true;
  score = 0;//Reset score

  while(isPlaying){
    drawScore();
    drawHead(random(0, 320-20), random(0, 240-20));
  }
}

void drawScore(){
  tft.setCursor(1, 0);
  tft.setTextSize(2);
  tft.fillRect(0, 0, 50, 20, BLACK);
  tft.print(score);
  tft.print(" Headshots");
  delay(100);
}

void drawHead(int x, int y){
  unsigned long showtime;
  boolean showed = false;

  TSPoint p = ts.getPoint();
  digitalWrite(13, HIGH);
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
    //Difficulty changer
  if(score >= 0 && score<= 5)
    showtime = 8000;//8s
  else if(score >= 6 && score<= 10)
    showtime = 6000;//6s
  else if(score >= 11 && score<= 20)
    showtime = 4000;//4s
  else if(score < 20)
    showtime = 500;//2s

  //Draw logic
  tft.fillRoundRect(x, y, 65, 84, 5, BLACK); 
  tft.drawBitmap(x, y, HEAD, 65, 87, WHITE);
  showed = true;
  delay(200);

  //if image shown but not pressed
  if(showed == true){
    delay(showtime);
    tft.fillRoundRect(x, y, 65, 84, 5, BLACK);
    gameover();   
   }
   //if image shown but pressed 
   else if(showed == true && (p.z > MINPRESSURE && p.z < MAXPRESSURE)){
    p.x = tft.width()-(map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
    p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
    Serial.println("Head X positiion :");
    Serial.println(x);
    Serial.println("Head Y positiion :");
    Serial.println(y);
    Serial.println("Touched X positiion :");
    Serial.println(p.x);
    Serial.println("Touched Y positiion :");
    Serial.println(p.y);
    if((p.x >= x-20) && (p.x <= x+20)){
      if((p.y >= y-20)&&(p.y <= y+20)){
         tft.fillRoundRect(x, y, 320, 240, 5, BLACK);
         score++;
         showed = false;
      }
    }
   }
}

void gameover(){
  unsigned short timer = 6;
  tft.fillScreen(BLACK);
  tft.setCursor(120, 10);
  tft.setTextSize(2);

  tft.print("GAMEOVER");
  tft.setCursor(40, 60);
  tft.print("Game restart in ");
  
  tft.print("5sec");

  tft.setCursor(120, 80);
  tft.print("Score : ");
  tft.print(score);
  delay(5000);
  
  tft.fillScreen(BLACK);
}

