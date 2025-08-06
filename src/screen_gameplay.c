#include <definitions.h>
#include <raylib.h>
#include <stdio.h>
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
const float SNACK_SPEED = 3.0f;
const float CAMERA_ZOOM = 25.0f;
enum {UP,LEFT,DOWN,RIGHT};
/*
* Game state
*/
int gameState = MAIN_MENU;
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
	Color color;
	Vector2 position[MAX_SNAKE_SIZE];
	float movingSteps;
} Snack;
Snack snack = {0};
/*
* Input Settings
*/
int PauseKey = KEY_P;
/*
* Function Declarations
*/
void UpdateSnackDirection();
void ProcessPlayInputs();
void RestartGame();
void MoveSnack(Snack *snack);
void process_inputs_gameplay();
void InitSnack(Vector2 position, int size, int direction);
bool CheckCollisionWithBounds(Snack *snack);
void init_gameplay(Color color ,int skin,int head)
{
	int direction = GetRandomValue(UP,RIGHT);
	snack.color = color;
	InitSnack((Vector2) {GRID_WIDTH/2,GRID_HEIGHT/2}, 5, direction);
	snack.alive = true;
    camera.zoom = CAMERA_ZOOM;
    camera.offset =(Vector2) {(float)SCREEN_WIDTH,(float)SCREEN_HEIGHT/2};
    camera.target =(Vector2) {(float)GRID_BOUNDS.width,(float)GRID_HEIGHT/2};
	gameState = PLAY;
}
void Render_gameplay()
{
	BeginDrawing();
	ClearBackground(BLUE);
	BeginMode2D(camera);
	// Draw grid bounds
	DrawRectangleLinesEx(GRID_BOUNDS,GRID_BOUNDS_THICKNESS , LIGHTGRAY);
	DrawRectangle(GRID_POSITION.x, GRID_POSITION.y, GRID_WIDTH * CELL_WIDTH, GRID_HEIGHT * CELL_WIDTH,ColorAlpha(LIGHTGRAY,0.5f));
		for(int i=0;i<snack.size;i++){
			if(i==snack.head) DrawRectangle(snack.position[i].x,snack.position[i].y,CELL_WIDTH,CELL_WIDTH,RED);
			else DrawRectangle(snack.position[i].x,snack.position[i].y,CELL_WIDTH,CELL_WIDTH,GREEN);
		}
	EndMode2D();
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
		}
		if (CheckCollisionWithBounds(&snack))
		{
			printf("snak dead!\n");
			RestartGame();
		}
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
		if (IsKeyDown(KEY_SPACE)) gameState = PLAY;
		break;
	case DEAD:
		if (IsKeyDown(KEY_SPACE)) RestartGame();
	default:
		break;
	}
}

void ProcessPlayInputs()
{
	if (IsKeyDown(PauseKey)) gameState = PAUSE;
	else if (gameState==PLAY) UpdateSnackDirection();
}
void RestartGame()
{
	InitSnack((Vector2){GRID_HEIGHT/2,GRID_WIDTH/2},1,GetRandomValue(UP,RIGHT));
	snack.alive = true;
	gameState = PLAY;
	
}
void UpdateSnackDirection()
{
	if (IsKeyDown(KEY_W))snack.direction = UP;
	else if (IsKeyDown(KEY_S)) snack.direction = DOWN;
	else if (IsKeyDown(KEY_D)) snack.direction = RIGHT;
	else if (IsKeyDown(KEY_A)) snack.direction = LEFT;
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
	// snake.headBnds.x = snack->position[snack->head].x;
	// snake.headBnds.y = snack->position[snack->head].y;
}

void InitSnack(Vector2 position, int size, int direction)
{
	snack.size = size;
	snack.head = 0;
	snack.movingSteps = 0;
	snack.speed = SNACK_SPEED;
	snack.gain = 0;
	snack.direction = direction;
	switch (direction)
	{
	case UP:
		for (int i = 0;i<size;i++)snack.position[i] = (Vector2) {position.x,position.y-i*CELL_WIDTH};
		break;
	case DOWN:
		for (int i = 0;i<size;i++)snack.position[i] = (Vector2) {position.x,position.y+i*CELL_WIDTH};
		break;
	case LEFT:
		for (int i = 0;i<size;i++)snack.position[i] = (Vector2) {position.x+i*CELL_WIDTH,position.y};
		break;
	case RIGHT:
		for (int i = 0;i<size;i++)snack.position[i] = (Vector2) {position.x-i*CELL_WIDTH,position.y};
		break;
	}
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