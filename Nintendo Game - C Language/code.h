// #ifndef CODE_SEEN
// #define CODE_SEEN

// #include "gba.h"


// typedef struct {
// 	int x, y;
// 	int direction;
// } CubePos;

// typedef struct {
// 	int x, y;
// } ManPos;

// typedef struct {
// 	CubePos firstCubePos;
// 	CubePos secondCubePos;
// 	CubePos thirdCubePos;
// 	ManPos manPos;
// 	int lives;
// 	int dead;
// 	int win;
// } GameLive;

// void startGame(GameLive *gameLive);

// void drawFirstGameState(GameLive *gameLive);
// void drawSecondGameState(GameLive *gameLive);
// void drawCubes(CubePos firstCubePos, CubePos secondCubePos, CubePos thirdCubePos);
// void drawRunningMan(ManPos manPos);
// void undrawGameState(GameLive *gameLive);

// int checkTouch(ManPos manPos, CubePos firstCubePos, CubePos secondCubePos, CubePos thirdCubePos);

// GameLive updateGame(GameLive *currGameLive, u32 keysPressedNow);

// #endif