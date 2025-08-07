#include <definitions.h>
#include <raylib.h>
#include <stdio.h>
#include <screen_gameplay.h>
#include <screen_mainmenu.h>

int gameState = MAIN_MENU;
int oldGameState = MAIN_MENU;
void DoTransition();
int main(int argc, char *argv[]) {
  InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"GUEMBOSNACK");
  SetTargetFPS(60);
  
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
  init_gameplay(SNAKE_COLORS[selected_color],0,0);
  gameState = PLAY;
}

void TransitionToMainMenu()
{
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