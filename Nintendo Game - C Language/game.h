// Sam Garvis

#ifndef GAME_H
#define GAME_H

#include "gba.h"

// this struct holds the location and the vertical motion of a stop sign
typedef struct {
	int x, y;
	int direction;
} CubePos;

// this sturct holds the position of the person
typedef struct {
	int x, y;
} ManPos;

// this struct contains all three stop signs and the person. It also contains 
// ints to show the lives and tell whether the player is alive or dead.
typedef struct {
	CubePos firstCubePos;
	CubePos secondCubePos;
	CubePos thirdCubePos;
	ManPos manPos;
	int lives;
	int dead;
	int win;
} GameLive;

void startGame(GameLive *gameLive);

void drawFirstGameState(GameLive *gameLive);
void drawSecondGameState(GameLive *gameLive);
void drawCubes(CubePos firstCubePos, CubePos secondCubePos, CubePos thirdCubePos);
void drawRunningMan(ManPos manPos);
void undrawGameState(GameLive *gameLive);

int checkTouch(ManPos manPos, CubePos firstCubePos, CubePos secondCubePos, CubePos thirdCubePos);

GameLive updateGame(GameLive *currGameLive, u32 keysPressedNow);

#endif
