/*******************************************************************************************
*
*   Gsnake game over screen v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_GSNAKE GAME OVER SCREEN_IMPLEMENTATION
*       #include "gui_Gsnake game over screen.h"
*
*       INIT: GuiGsnake game over screenState state = InitGuiGsnake game over screen();
*       DRAW: GuiGsnake game over screen(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 github.com/osdv . All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_GSNAKE GAME OVER SCREEN_H
#define GUI_GSNAKE GAME OVER SCREEN_H

typedef struct {
    

    Rectangle layoutRecs[3];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiGsnake game over screenState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiGsnake game over screenState InitGuiGsnake game over screen(void);
void GuiGsnake game over screen(GuiGsnake game over screenState *state);
static void PlayAgainButton();
static void MainMenuButton();

#ifdef __cplusplus
}
#endif

#endif // GUI_GSNAKE GAME OVER SCREEN_H

/***********************************************************************************
*
*   GUI_GSNAKE GAME OVER SCREEN IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_GSNAKE GAME OVER SCREEN_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiGsnake game over screenState InitGuiGsnake game over screen(void)
{
    GuiGsnake game over screenState state = { 0 };

    

    state.layoutRecs[0] = (Rectangle){ 352, 432, 152, 40 };
    state.layoutRecs[1] = (Rectangle){ 712, 432, 152, 40 };
    state.layoutRecs[2] = (Rectangle){ 336, 352, 512, 16 };

    // Custom variables initialization

    return state;
}
static void PlayAgainButton()
{
    // TODO: Implement control logic
}
static void MainMenuButton()
{
    // TODO: Implement control logic
}


void GuiGsnake game over screen(GuiGsnake game over screenState *state)
{
    if (GuiButton(state->layoutRecs[0], "Play Again [SPACE]")) PlayAgainButton(); 
    if (GuiButton(state->layoutRecs[1], "MAIN MENU")) MainMenuButton(); 
    GuiLine(state->layoutRecs[2], NULL);
}

#endif // GUI_GSNAKE GAME OVER SCREEN_IMPLEMENTATION
