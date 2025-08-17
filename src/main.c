#include <definitions.h>
#include <raylib.h>
#include <stdio.h>
#include <screen_gameplay.h>
#include <screen_mainmenu.h>

GameResources gameResources;
GameplayOptions gameplayOptions;
int gameState = MAIN_MENU;
int oldGameState = MAIN_MENU;
void DoTransition();
void LoadGameResources();
int main(int argc, char *argv[]) {
  InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"GUEMBOSNACK");
  SetTargetFPS(60);
  LoadGameResources();
  LoadMainMenuScreen();
  while (!WindowShouldClose())
  {
    DoTransition();
    oldGameState = gameState; // Store the old game state for transition checks
    switch (gameState)
    {
      case MAIN_MENU:
      UpdateMainMenuScreen();
      RenderMainMenu();
      break;
      case PLAY:
      case PAUSE:
      case DEAD:
        update_gameplay();
        Render_gameplay();
        break;
    default:
      break;
    }
  }
  
  return 0;
}

void TransitionToGameplay()
{
  UnloadMainMenuScreen();
  init_gameplay();
  gameState = PLAY;
}

void TransitionToMainMenu()
{
  UnlaodGameplayScreen();
  InitMainMenu();
  gameState = MAIN_MENU;
}

void DoTransition()
{
  if (gameState != oldGameState)
  {
    switch (gameState)
    {
    case PLAY:
      if(oldGameState==MAIN_MENU)TransitionToGameplay();
      break;
    case MAIN_MENU:
      TransitionToMainMenu();
      break;
    default:
      break;
    }
  }
}

/*
emcmake cmake -S . -B build -G Ninja
emmake ninja -C build
*/
// Load Resources in RAM
void LoadGameResources()
{
  // Load characters skins
  FilePathList paths;
  paths = LoadDirectoryFiles(CHARACTER_TEXTURES_PATH);
  gameResources.characters_count = MIN(paths.capacity,MAX_CHARACTERS);
  for (int i=0;i<gameResources.characters_count;i++)
  {
    gameResources.snake_characters[i] = LoadImage(paths.paths[i]);
  }
  UnloadDirectoryFiles(paths);
  // Load food textures
  paths = LoadDirectoryFiles(FOOD_TEXTURES_PATH);
  gameResources.food_skins_count = MIN(MAX_FOOD_SKINS,paths.capacity);
  for (int i=0;i<gameResources.food_skins_count;i++)
  {
    gameResources.food_skin[i] = LoadImage(paths.paths[i]);
  }
  paths = LoadDirectoryFiles(SKINZ_TEXTURES_PATH);
  gameResources.skins_count = MIN(MAX_SNAKE_SKINS,paths.capacity);
  for (int i=0;i<gameResources.skins_count;i++)
  {
    gameResources.skins[i] = LoadImage(paths.paths[i]);
  }  
}