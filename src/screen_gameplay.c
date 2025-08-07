#include <definitions.h>
#include <screen_gameplay.h>
#include <raylib.h>
#include <stdio.h>
#include <time.h>
const int GRID_WIDTH = 50;
const int GRID_HEIGHT = 35;
const float GRID_BOUNDS_THICKNESS = 0.5f;
const Vector2 GRID_POSITION = (Vector2) {0,0};
const Rectangle GRID_BOUNDS = {-GRID_BOUNDS_THICKNESS, -GRID_BOUNDS_THICKNESS, GRID_WIDTH+GRID_BOUNDS_THICKNESS*2, GRID_HEIGHT+GRID_BOUNDS_THICKNESS*2};
const float CELL_WIDTH = 1.0f;
// Camera
Camera2D camera={0} ;
/*
* Snake definition
*/
#define MAX_SNAKE_SIZE 256
const float SNAKE_WIDTH = 0; // TODO()
const float POINT_WIDTH = 0; //TODO()
const float SNACK_SPEED = 3.5f;
const float SNACK_RUN_FACTOR = 2.0f;
const float CAMERA_ZOOM = 25.0f;
enum {UP,LEFT,DOWN,RIGHT};
/*
* Game state
*/

float deltaTime=0;
// Snake struct
typedef struct {
	Texture2D skin;
	Texture2D texHead;
	int head;
	int size;
	int gain;
	float speed;
	bool alive;
	int direction;// U:up , D:down , R:right , L:left
	int lastStepDirection;
	Color color;
	Vector2 position[MAX_SNAKE_SIZE];
	float movingSteps;
} Snack;
Snack snack = {0};
/*
* Snake Point
*/
typedef struct {
	Color color;
	bool ready;
	Rectangle bounds;
	Texture2D tex;
} SnackPoint;
SnackPoint point={
	.color = BROWN,
	.ready = false,
	.bounds = {0,0,CELL_WIDTH,CELL_WIDTH},
	.tex = {0}
};
/*
* Count Score
*/
int score = 0;
int highScore = 0;
/*
* Fonts and messages
*/
// Gameover Screen
const char* YouDiedMsg = "YOU DIED !";
const float YouDiedMsgSpacing = 1.0f;
const int YouDIedMsgFontSize = 100;
Vector2 YouDiedMsgPosition = {0};
// Fonts
Font DepixelFont ={0};
const int DepixelLoadSize=100;
// Play Again and Main Menu Buttons
Rectangle PlayAgainButton = {0,0,0,0}; 
Rectangle MainMenuButton = {0,0,0,0}; 
/*
* Input Settings
*/
int PauseKey = KEY_P;
int MOVE_UP_KEY =KEY_W;
int MOVE_DOWN_KEY = KEY_S;
int MOVE_RIGHT_KEY = KEY_D;
int MOVE_LEFT_KEY=KEY_A;
/*
* Function Declarations
*/
void UpdateSnackDirection(Snack *snack);
void UpdateSnackSpeed(Snack *snack);
void ProcessPlayInputs();
void RestartGame();
void MoveSnack(Snack *snack);
void process_inputs_gameplay();
void InitSnack(Vector2 position, int size, int direction);
bool CheckCollisionWithBounds(Snack *snack);
bool CheckSnackSelfCollision(Snack *snack);
void updateSnackSize(Snack *snack);
void generatePoint(SnackPoint *point);
void init_gameplay(Color color ,int skin,int head)
{
	SetRandomSeed((unsigned int)time(NULL));
	LoadGameplayScreen();
	int direction = GetRandomValue(UP,RIGHT);
	snack.color = color;
	InitSnack((Vector2) {GRID_WIDTH/2,GRID_HEIGHT/2}, 1, direction);
	snack.alive = true;
    camera.zoom = CAMERA_ZOOM;
    camera.offset =(Vector2) {(float)SCREEN_WIDTH,(float)SCREEN_HEIGHT/2};
    camera.target =(Vector2) {(float)GRID_BOUNDS.width,(float)GRID_HEIGHT/2};
	gameState = PLAY;
	score = 0;
}
void Render_gameplay()
{
	BeginDrawing();
	switch (gameState)
	{
	case PLAY:
	ClearBackground(BLUE);
	BeginMode2D(camera);
	// Draw grid bounds
	DrawRectangleLinesEx(GRID_BOUNDS,GRID_BOUNDS_THICKNESS , LIGHTGRAY);
	DrawRectangle(GRID_POSITION.x, GRID_POSITION.y, GRID_WIDTH * CELL_WIDTH, GRID_HEIGHT * CELL_WIDTH,ColorAlpha(LIGHTGRAY,0.5f));
		for(int i=0;i<snack.size;i++){
			if(i==snack.head) DrawRectangle(snack.position[i].x,snack.position[i].y,CELL_WIDTH,CELL_WIDTH,RED);
			else DrawRectangle(snack.position[i].x,snack.position[i].y,CELL_WIDTH,CELL_WIDTH,snack.color);
		}
	if (point.ready) DrawRectangleRec(point.bounds,point.color);		
	EndMode2D();
	// Draw score
	DrawText(TextFormat("Score: %d",score),10,10, 18, RAYWHITE);
	DrawText(TextFormat("High Score: %d",highScore),10,30, 18 , RAYWHITE);
		break;
	case PAUSE:
			ClearBackground(ColorAlpha(BLACK,0.5f));
			DrawTextEx(DepixelFont,"PAUSED", (Vector2){SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 20}, 40, YouDiedMsgSpacing, RAYWHITE);
			DrawTextEx(DepixelFont,"Press [SPACE] to continue", (Vector2){SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 + 20}, 20, YouDiedMsgSpacing, RAYWHITE);
		break;
	case DEAD:
		ClearBackground(ColorAlpha(PINK,0.7));
		DrawTextEx(DepixelFont,YouDiedMsg,YouDiedMsgPosition,YouDIedMsgFontSize,YouDiedMsgSpacing,RAYWHITE);
		DrawRectangleRec(PlayAgainButton,ColorAlpha(GREEN,0.5f));
		DrawTextEx(DepixelFont,"Play Again [SPACE]", (Vector2){PlayAgainButton.x + 10, PlayAgainButton.y + 10}, 16, YouDiedMsgSpacing, RAYWHITE);
		DrawRectangleRec(MainMenuButton,ColorAlpha(GREEN,0.5f));
		DrawTextEx(DepixelFont,"Main Menu [Q]", (Vector2){MainMenuButton.x + 10, MainMenuButton.y + 10}, 16, YouDiedMsgSpacing, RAYWHITE);
	}
	EndDrawing();
}
void update_gameplay()
{
	deltaTime = GetFrameTime();
	process_inputs_gameplay();
	if (gameState==PLAY){
		snack.movingSteps += deltaTime * snack.speed;
		if (snack.movingSteps >=1){
			snack.movingSteps = 0;
			MoveSnack(&snack);
			printf("Snack Position: %f %f\n",snack.position[snack.head].x,snack.position[snack.head].y);
			if (CheckCollisionWithBounds(&snack)||CheckSnackSelfCollision(&snack))
			{
				printf("snake dead!\n");
				gameState = DEAD;
			}
			if (!point.ready) generatePoint(&point);
			else if (point.ready && CheckCollisionRecs((Rectangle){snack.position[snack.head].x,snack.position[snack.head].y,CELL_WIDTH,CELL_WIDTH},point.bounds)) {
				score++;
				snack.gain++;
				point.ready = false;
				updateSnackSize(&snack);
			}
		}
		updateSnackSize(&snack);
	}
}

void process_inputs_gameplay()
{
	switch (gameState)
	{
	case PLAY:
		ProcessPlayInputs();
		break;
	case PAUSE:
		if (IsKeyPressed(KEY_SPACE)) gameState = PLAY;
		break;
	case DEAD:
		if (IsKeyDown(KEY_SPACE)) RestartGame();
		else if (IsKeyDown(KEY_Q)) gameState = MAIN_MENU;
	default:
		break;
	}
}

void ProcessPlayInputs()
{
	if (IsKeyDown(PauseKey)) gameState = PAUSE;
	else if (gameState==PLAY) {
		UpdateSnackDirection(&snack);
		UpdateSnackSpeed(&snack);
	}
}
void RestartGame()
{
	InitSnack((Vector2){GRID_HEIGHT/2,GRID_WIDTH/2},1,GetRandomValue(UP,RIGHT));
	snack.alive = true;
	gameState = PLAY;
	if (score > highScore) highScore = score;
	score = 0;
	
}
void UpdateSnackDirection(Snack *snack)
{
	switch (snack->lastStepDirection)
	{
	case UP:
	case DOWN:
		if (IsKeyDown(MOVE_RIGHT_KEY)) snack->direction = RIGHT;
		else if (IsKeyDown(MOVE_LEFT_KEY)) snack->direction = LEFT;
		break;
	case RIGHT:
	case LEFT:
		if (IsKeyDown(MOVE_UP_KEY))snack->direction = UP;
		else if (IsKeyDown(MOVE_DOWN_KEY)) snack->direction = DOWN;
		break;
	}
}
void MoveSnack(Snack *snack){
	int tmp=snack->head;
	snack->head = (snack->head - 1);
	if (snack->head<0)snack->head = snack->size-1;
	switch (snack->direction){
		case UP:snack->position[snack->head] = (Vector2){snack->position[tmp].x,snack->position[tmp].y-CELL_WIDTH};break;
		case DOWN:snack->position[snack->head] = (Vector2){snack->position[tmp].x,snack->position[tmp].y+CELL_WIDTH};break;
		case LEFT:snack->position[snack->head] = (Vector2){snack->position[tmp].x-CELL_WIDTH,snack->position[tmp].y};break;
		case RIGHT:snack->position[snack->head] = (Vector2){snack->position[tmp].x+CELL_WIDTH,snack->position[tmp].y};break;
	}	
	snack->lastStepDirection = snack->direction;
	// snake.headBnds.x = snack->position[snack->head].x;
	// snake.headBnds.y = snack->position[snack->head].y;
}

void InitSnack(Vector2 position, int size, int direction)
{
	snack.size = 1;
	snack.head = 0;
	snack.movingSteps = 0;
	snack.speed = SNACK_SPEED;
	snack.gain = size - 1;
	snack.direction = direction;
	snack.lastStepDirection=direction;
	snack.position[0]=position;
}

bool CheckCollisionWithBounds(Snack *snack)
{
	if (snack->position[snack->head].x < GRID_POSITION.x || 
		snack->position[snack->head].x >= GRID_POSITION.x + GRID_WIDTH ||
		snack->position[snack->head].y < GRID_POSITION.y || 
		snack->position[snack->head].y >= GRID_POSITION.y + GRID_HEIGHT)
	{
		return true;
	}
	return false;
}

void updateSnackSize(Snack *snack)
{
	if (snack->head) return;
	for (int i =0 ; i<snack->gain;i++){
		snack->position[snack->size] = snack->position[snack->size-1];
		snack->size++;
	}
	snack->gain=0;
}

bool CheckSnackSelfCollision(Snack *snack)
{
	if (snack->size<5) return false;
	Rectangle head = {snack->position[snack->head].x,snack->position[snack->head].y,CELL_WIDTH,CELL_WIDTH};
	Rectangle core = {0,0,CELL_WIDTH,CELL_WIDTH};
	for (int i =0;i<snack->size;i++)
	{
		if (i!=snack->head)
		{
			core.x = snack->position[i].x;
			core.y = snack->position[i].y;
			if (CheckCollisionRecs(head,core)) return true;
		}
	}
	return false;
}

void UpdateSnackSpeed(Snack *snack)
{
	if ((IsKeyDown(MOVE_UP_KEY)&& snack->direction==UP) || 
	(IsKeyDown(MOVE_DOWN_KEY) && snack->direction==DOWN )|| 
	(IsKeyDown(MOVE_RIGHT_KEY) && snack->direction==RIGHT )|| 
	(IsKeyDown(MOVE_LEFT_KEY)&& snack->direction==LEFT))  snack->speed = SNACK_SPEED * SNACK_RUN_FACTOR;
	else snack->speed = SNACK_SPEED;
}

void LoadGameplayScreen()
{
	DepixelFont = LoadFontEx(DE_PIXEL_FONT_PATH,DepixelLoadSize,(void *)0,0);
	Vector2 TextMesure =MeasureTextEx(DepixelFont,YouDiedMsg,YouDIedMsgFontSize,YouDiedMsgSpacing);
	YouDiedMsgPosition = (Vector2){SCREEN_WIDTH/2 - TextMesure.x/2,
									SCREEN_HEIGHT/2 - TextMesure.y/2};
	PlayAgainButton = (Rectangle){
		SCREEN_WIDTH/2 - 300,
		SCREEN_HEIGHT/2 + 10 + TextMesure.y,
		200,50
	};
	MainMenuButton = (Rectangle){
		SCREEN_WIDTH/2 + 100,
		SCREEN_HEIGHT/2 + 10 + TextMesure.y,
		200,50
	};
}

void generatePoint(SnackPoint *point)
{
	do {
		point->bounds.x=GetRandomValue(0,GRID_WIDTH-CELL_WIDTH);
		point->bounds.y= GetRandomValue(0,GRID_HEIGHT-CELL_WIDTH);
	} while (CheckCollisionRecs((Rectangle){snack.position[snack.head].x,snack.position[snack.head].y,CELL_WIDTH,CELL_WIDTH},point->bounds));
	point->ready = true;
	printf("Point generated at: %f %f\n",point->bounds.x,point->bounds.y);

}