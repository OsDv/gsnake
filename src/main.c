#include <definitions.h>
#include <raylib.h>
#include <stdio.h>
#include <screen_gameplay.h>




int main(int argc, char *argv[]) {
  InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"GUEMBOSNACK");
  SetTargetFPS(60);
  
  init_gameplay(RED,0,0);
  while (!WindowShouldClose())
  {
    // TODO()ToggleFullscreen(); // With 'F' press 
    update_gameplay();
    Render_gameplay();
  }
  
  return 0;
}
