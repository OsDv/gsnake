#include <definitions.h>
#include <raylib.h>
#include <screen_mainmenu.h>

const Color SNAKE_COLORS[] = {
	GREEN,
	PINK,
	LIME,
	GOLD,
	BEIGE,
	ORANGE,
};

enum {SETTING_COLOR,SETTING_CHARACTER,SETTING_FOOD_SKIN,SETTING_SKIN};
int optionsCount = 4;
int colors_count = sizeof(SNAKE_COLORS) / sizeof(SNAKE_COLORS[0]);
int selected_color = 0; // Default color index
int selected_character = 0;
int selected_food_skin =0 ;
int selected_skin = 0 ;

const char* TitleScreenMsg = "Guembo Snake !";
const float TitleScreenMsgSpacing = 1.0f;
const int TitleScreenMsgFontSize = 100;
Vector2 TitleScreenMsgPosition = {0};
// Fonts
Font TitleFont ={0};
const int TitleFontSize=100;
int TargetOption = SETTING_COLOR;
// 
void modifyOption(int key);
//
void RenderMainMenu()
{
	Vector2 showPosition={SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 50};
	Vector2 showDimentions = {100,100};
	BeginDrawing();
	ClearBackground(BLUE);
	DrawTextEx(TitleFont, TitleScreenMsg, TitleScreenMsgPosition, TitleScreenMsgFontSize, TitleScreenMsgSpacing, BLACK);
	switch (TargetOption)
	{
	case SETTING_COLOR:
		DrawText("Chose your snake color:", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 100, 20, BLACK);
		// Draw Selected Color

		DrawRectangleV(showPosition, showDimentions, SNAKE_COLORS[selected_color]);
		break;
	case SETTING_CHARACTER:
		DrawText("Chose your snake character:", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 100, 20, BLACK);
		DrawTextureEx(gameplayOptions.characterSkin,showPosition,0,showDimentions.x/gameplayOptions.characterSkin.width,WHITE);
		break;
	case SETTING_FOOD_SKIN:
		DrawText("Chose Food Skin:", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 100, 20, BLACK);
		DrawTextureEx(gameplayOptions.foodSkin,showPosition,0,showDimentions.x/gameplayOptions.foodSkin.width,WHITE);
		break;
	case SETTING_SKIN:
		DrawText("Chose snake Skin:", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 100, 20, BLACK);
		if (selected_skin>=0)DrawTextureEx(gameplayOptions.snakeSkin,showPosition,0,showDimentions.x/gameplayOptions.snakeSkin.width,WHITE);
		else DrawText("NONE!", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2, 20, BLACK);
		
		break;
	default:
		break;
	}
	// Chose Color Prompt

	EndDrawing();
}
void LoadMainMenuScreen()
{
	TitleFont = LoadFontEx(DE_PIXEL_FONT_PATH,TitleFontSize,(void *)0,0);
	Vector2 TextMesure =MeasureTextEx(TitleFont,TitleScreenMsg,TitleScreenMsgFontSize,TitleScreenMsgSpacing);
	TitleScreenMsgPosition = (Vector2){SCREEN_WIDTH/2 - TextMesure.x/2,
									SCREEN_HEIGHT/2 -300};
	if(gameResources.characters_count>0)gameplayOptions.characterSkin = LoadTextureFromImage(gameResources.snake_characters[0]);
	if(gameResources.food_skins_count>0)gameplayOptions.foodSkin = LoadTextureFromImage(gameResources.food_skin[0]);
	gameplayOptions.snakeColor = SNAKE_COLORS[selected_color];
	if (gameResources.skins_count>0)gameplayOptions.snakeSkin = LoadTextureFromImage(gameResources.skins[0]);
	
}

void UnloadMainMenuScreen()
{
	UnloadFont(TitleFont);
}
void UpdateMainMenuScreen()
{
	if(IsKeyPressed(KEY_RIGHT))modifyOption(KEY_RIGHT);
	else if(IsKeyPressed(KEY_LEFT))modifyOption(KEY_LEFT);
	// Swich between options
	if (IsKeyPressed(KEY_UP)) {
		TargetOption = (TargetOption + 1) % optionsCount; 
	} else if (IsKeyPressed(KEY_DOWN)) {
		TargetOption = (TargetOption - 1 + optionsCount) % optionsCount;
	}
	// Check for start game input
	if (IsKeyPressed(KEY_ENTER)) {
		gameState = PLAY; // Change game state to start the game
	}
}
void InitMainMenu()
{
	LoadMainMenuScreen();
	selected_color = 0; // Reset to default color
	int selected_character = 0;
	int selected_food_skin =0 ;
}

void modifyOption(int key)
{
	bool changed = false;
	switch (TargetOption)
	{
	case SETTING_COLOR:
		// Check for color selection input
		if (key==KEY_RIGHT){
			selected_color = (selected_color + 1) % colors_count; 
		} else if (key==KEY_LEFT) {
			selected_color = (selected_color - 1 + colors_count) % colors_count; 
		}		
		break;
	case SETTING_CHARACTER:
		// Check for color selection input
		if (key==KEY_RIGHT) {
			changed = true;
			selected_character = (selected_character + 1) % gameResources.characters_count; 
		} else if (key==KEY_LEFT) {
			changed = true;
			selected_character = (selected_character - 1 + gameResources.characters_count) % gameResources.characters_count;
		}
		if (changed){
			UnloadTexture(gameplayOptions.characterSkin);
			gameplayOptions.characterSkin = LoadTextureFromImage(gameResources.snake_characters[selected_character]);
		}
		break;
	case SETTING_FOOD_SKIN:
		// Check for color selection input
		if (key==KEY_RIGHT) {
			changed = true;
			selected_food_skin = (selected_food_skin + 1) % gameResources.food_skins_count; 
		} else if (key==KEY_LEFT) {
			changed = true;
			selected_food_skin = (selected_food_skin - 1 + gameResources.food_skins_count) % gameResources.food_skins_count;
		}
		if (changed){
			UnloadTexture(gameplayOptions.foodSkin);
			gameplayOptions.foodSkin = LoadTextureFromImage(gameResources.food_skin[selected_food_skin]);
		}
		break;
	case SETTING_SKIN:
		if (key==KEY_RIGHT) {
			changed = true;
			selected_skin +=1;
			if (selected_skin>=gameResources.skins_count) selected_skin=-1;
		} else if (key==KEY_LEFT) {
			changed = true;
			selected_skin -=1;
			if (selected_skin<-1) selected_skin = gameResources.skins_count -1 ;
		}
		if (changed){
			UnloadTexture(gameplayOptions.snakeSkin);
			if (selected_skin>=0)gameplayOptions.snakeSkin = LoadTextureFromImage(gameResources.skins[selected_skin]);
		}
		break;
	default:
		break;
	}
}