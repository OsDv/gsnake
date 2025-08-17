#ifndef _OSDV_GSNAKE_DEFINITIONS_
#define _OSDV_GSNAKE_DEFINITIONS_ 0
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#include <raylib.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CELLS_SCALE 32
#define DE_PIXEL_FONT_PATH "./res/fonts/DePixelHalbfett.ttf"
#define FOOD_TEXTURES_PATH "res/textures/food/"
#define CHARACTER_TEXTURES_PATH "res/textures/character/"
#define SKINZ_TEXTURES_PATH "res/textures/skin/"
enum GAME_STATE {PLAY,MAIN_MENU,DEAD,PAUSE};
extern int gameState;
#define MAX_CHARACTERS 4
#define MAX_FOOD_SKINS 2
#define MAX_SNAKE_SKINS 2
typedef struct
{
	int characters_count;
	Image snake_characters[MAX_CHARACTERS];
	Image food_skin[MAX_FOOD_SKINS];
	int food_skins_count;
	int snake_skins_coutn;
	Image snake_skins[MAX_SNAKE_SKINS];
	Image skins[MAX_SNAKE_SKINS];
	int skins_count;
}GameResources;
typedef struct 
{
	Color snakeColor;
	Texture2D characterSkin;
	Texture2D foodSkin;
	Texture2D snakeSkin;
} GameplayOptions;
extern GameResources gameResources;
extern GameplayOptions gameplayOptions;

#endif