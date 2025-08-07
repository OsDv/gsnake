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
int colors_count = sizeof(SNAKE_COLORS) / sizeof(SNAKE_COLORS[0]);
int selected_color = 0; // Default color index

const char* TitleScreenMsg = "Guembo Snake !";
const float TitleScreenMsgSpacing = 1.0f;
const int TitleScreenMsgFontSize = 100;
Vector2 TitleScreenMsgPosition = {0};
// Fonts
Font TitleFont ={0};
const int TitleFontSize=100;

void RenderMainMenu()
{
	BeginDrawing();
	ClearBackground(BLUE);
	DrawTextEx(TitleFont, TitleScreenMsg, TitleScreenMsgPosition, TitleScreenMsgFontSize, TitleScreenMsgSpacing, BLACK);
	// Chose Color Prompt
	DrawText("Chose your snake color:", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 100, 20, BLACK);
	// Draw Selected Color
	DrawRectangle(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 50, 100, 100, SNAKE_COLORS[selected_color]);
	EndDrawing();
}
void LoadMainMenuScreen()
{
	TitleFont = LoadFontEx(DE_PIXEL_FONT_PATH,TitleFontSize,(void *)0,0);
	Vector2 TextMesure =MeasureTextEx(TitleFont,TitleScreenMsg,TitleScreenMsgFontSize,TitleScreenMsgSpacing);
	TitleScreenMsgPosition = (Vector2){SCREEN_WIDTH/2 - TextMesure.x/2,
									SCREEN_HEIGHT/2 -300};

}

void UnloadMainMenuScreen()
{
	UnloadFont(TitleFont);
}
void UpdateMainMenuScreen()
{
	// Check for color selection input
	if (IsKeyPressed(KEY_RIGHT)) {
		selected_color = (selected_color + 1) % colors_count; // Cycle through colors
	} else if (IsKeyPressed(KEY_LEFT)) {
		selected_color = (selected_color - 1 + colors_count) % colors_count; // Cycle through colors
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
}