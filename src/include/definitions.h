#ifndef _OSDV_GSNAKE_DEFINITIONS_
#define _OSDV_GSNAKE_DEFINITIONS_ 0
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#include <raylib.h>
#define DE_PIXEL_FONT_PATH "./res/fonts/DePixelHalbfett.ttf"

enum GAME_STATE {PLAY,MAIN_MENU,DEAD,PAUSE};
extern int gameState;
#endif