// Sam Garvis

#include "game.h"

#include <stdio.h>
#include <stdbool.h>
#include "gba.h"
#include "./images/stopsign.h"
#include "./images/runningman.h"

// This function initilializes a game. It should only run when 
// first going from the home screen into the game.
void startGame(GameLive* gameLive) {
	gameLive->lives = 3;
	gameLive->dead = 0;
	gameLive->win = 0;


	(gameLive->manPos).x = 0;
    (gameLive->manPos).y = 80;


	(gameLive->firstCubePos).x = 60;
    (gameLive->firstCubePos).y = 80;
    (gameLive->firstCubePos).direction = 0;

    (gameLive->secondCubePos).x = 115;
    (gameLive->secondCubePos).y = 80;
    (gameLive->secondCubePos).direction = 1;

    (gameLive->thirdCubePos).x = 170;
    (gameLive->thirdCubePos).y = 80;
    (gameLive->thirdCubePos).direction = 0;
}

// This initilizes the drawing of the game. This one is only used to start the game because you 
// don't need to draw "Lives: " every time. You just need to update the lives number.
void drawFirstGameState(GameLive* gameLive) {
	// redraws the stop signs and the person
	drawCubes(gameLive->firstCubePos, gameLive->secondCubePos, gameLive->thirdCubePos);
	drawRunningMan(gameLive->manPos);
	// draws the lives with initializing at 3
	drawString(0, 0, "Lives: 3", RED);
}

// This is the draw function that is called on a loop because it is shorter and more efficient
// than the drawFirstGameState function.
void drawSecondGameState(GameLive* gameLive) {
	// redraws the stop signs and the person
	drawCubes(gameLive->firstCubePos, gameLive->secondCubePos, gameLive->thirdCubePos);
	drawRunningMan(gameLive->manPos);
	// rewrites the lives number
	char str[1];
    sprintf(str, "%i", (gameLive->lives));
    drawString(0, 42, str, WHITE);
}

// This is a helper function to drawGameState that draws all three stop signs.
void drawCubes(CubePos firstCubePos, CubePos secondCubePos, CubePos thirdCubePos) {
	drawImageDMA(firstCubePos.x, firstCubePos.y, 16, 12, stopsign);

	drawImageDMA(secondCubePos.x, secondCubePos.y, 16, 12, stopsign);

	drawImageDMA(thirdCubePos.x, thirdCubePos.y, 16, 12, stopsign);
}

// This is a helper function to drawGameState that draws the moving person.
void drawRunningMan(ManPos manPos) {
	drawImageDMA(manPos.x, manPos.y, 19, 14, runningman);
}

// This function undraws each state as you progress to the next one.
// This is needed because if it wasn't implemented then the objects
// would move around leaving traces and fill up the screen.
void undrawGameState(GameLive *gameLive) {
	// draw the background color over the 3 signs and the player
	drawRectDMA((gameLive->manPos).x, (gameLive->manPos).y, 19, 14, GREEN);
	drawRectDMA((gameLive->firstCubePos).x, (gameLive->firstCubePos).y, 16, 12, GREEN);
	drawRectDMA((gameLive->secondCubePos).x, (gameLive->secondCubePos).y, 16, 12, GREEN);
	drawRectDMA((gameLive->thirdCubePos).x, (gameLive->thirdCubePos).y, 16, 12, GREEN);

	// draw the background color over the lives shown
	drawRectDMA(42, 0, 6, 8, GREEN);
}


// This function checks if the moving person touched any of the three stop signs.
// This is needed because if they touch then the lives of the player decrease by 1.
int checkTouch(ManPos manPos, CubePos firstCubePos, CubePos secondCubePos, CubePos thirdCubePos) {
	// initialize the edges for all 4 objects
	int manWidth = 19;
	int manHeight = 14;
	int manLeft, manRight, manBottom, manTop;
	manLeft = manPos.x;
	manRight = manPos.x + manWidth;
	manTop = manPos.y;
	manBottom = manPos.y + manHeight;

	int signWidth = 16;
	int signHeight = 12;
	int sign1Left, sign1Right, sign1Bottom, sign1Top, sign2Left, sign2Right, sign2Bottom, sign2Top, sign3Left, sign3Right, sign3Bottom, sign3Top;

	sign1Left = 60;
	sign1Right = 60 + signWidth;
	sign1Top = firstCubePos.y;
	sign1Bottom = firstCubePos.y + signHeight;

	sign2Left = 115;
	sign2Right = 115 + signWidth;
	sign2Top = secondCubePos.y;
	sign2Bottom = secondCubePos.y + signHeight;

	sign3Left = 170;
	sign3Right = 170 + signWidth;
	sign3Top = thirdCubePos.y;
	sign3Bottom = thirdCubePos.y + signHeight;

	// check if the player is touching any of the signs
	if (manRight >= sign1Left && manLeft <= sign1Right && manBottom >= sign1Top && manTop <= sign1Bottom) {
		return 1;
	} else if (manRight >= sign2Left && manLeft <= sign2Right && manBottom >= sign2Top && manTop <= sign2Bottom) {
		return 1;
	} else if (manRight >= sign3Left && manLeft <= sign3Right && manBottom >= sign3Top && manTop <= sign3Bottom) {
		return 1;
	}
	return 0;
}

// This function moves the objects around at each iteration. It will move the stop signs
// up and down. It will also move the player depending on which keys are pressed.
// This function also calls checkTouch and checks if the player won.
GameLive updateGame(GameLive* currGameLive, u32 keysPressedNow) {
	GameLive newGameLive = *currGameLive;

	// check each sign to see whether it needs to continue moving up or down or 
	// if it needs to change directions from hitting an edge
	if ((newGameLive.firstCubePos).y == 0) {
		(newGameLive.firstCubePos).direction = 0;
		(newGameLive.firstCubePos).y += 4;
	} else if ((newGameLive.firstCubePos).y + 12 == 160) {
		(newGameLive.firstCubePos).direction = 1;
		(newGameLive.firstCubePos).y -= 4;
	} else if ((newGameLive.firstCubePos).direction == 1) {
		(newGameLive.firstCubePos).y -= 4;
	} else {
		(newGameLive.firstCubePos).y += 4;
	}

	if ((newGameLive.secondCubePos).y == 0) {
		(newGameLive.secondCubePos).direction = 0;
		(newGameLive.secondCubePos).y += 4;
	} else if ((newGameLive.secondCubePos).y + 12 == 160) {
		(newGameLive.secondCubePos).direction = 1;
		(newGameLive.secondCubePos).y -= 4;
	} else if ((newGameLive.secondCubePos).direction == 1) {
		(newGameLive.secondCubePos).y -= 4;
	} else {
		(newGameLive.secondCubePos).y += 4;
	}

	if ((newGameLive.thirdCubePos).y == 0) {
		(newGameLive.thirdCubePos).direction = 0;
		(newGameLive.thirdCubePos).y += 4;
	} else if ((newGameLive.thirdCubePos).y + 12 == 160) {
		(newGameLive.thirdCubePos).direction = 1;
		(newGameLive.thirdCubePos).y -= 4;
	} else if ((newGameLive.thirdCubePos).direction == 1) {
		(newGameLive.thirdCubePos).y -= 4;
	} else {
		(newGameLive.thirdCubePos).y += 4;
	}

	// if player presses left, right, up, or down arrow move them as such assuming they have room
	if (KEY_DOWN(BUTTON_LEFT, keysPressedNow)) {
        if ((newGameLive.manPos).x > 19) {
            (newGameLive.manPos).x -= 1;
        }
    }
	if (KEY_DOWN(BUTTON_RIGHT, keysPressedNow)) {
        if ((newGameLive.manPos).x < 221) {
            (newGameLive.manPos).x += 1;
        }
    }
    if (KEY_DOWN(BUTTON_DOWN, keysPressedNow)) {
        if ((newGameLive.manPos).y < 146) {
            (newGameLive.manPos).y += 1;
        }
    }
    if (KEY_DOWN(BUTTON_UP, keysPressedNow)) {
        if ((newGameLive.manPos).y > 14) {
            (newGameLive.manPos).y -= 1;
        }
    }

    // check if the player reach the far edge and won
    if (newGameLive.manPos.x + 19 == 240) {
    	newGameLive.win = 1;
    }

    // if the player touched a sign then decrease lives by 1 and move player to beginning
    if (checkTouch((newGameLive.manPos), (newGameLive.firstCubePos), (newGameLive.secondCubePos), (newGameLive.thirdCubePos)) == 1) {
    	newGameLive.lives -= 1;
    	if (newGameLive.lives == 0) {
    		newGameLive.dead = 1;
    	}
    	(newGameLive.manPos).x = 0;
		(newGameLive.manPos).y = 80;

    }

    // return this updated game state which will become the current game state
    return newGameLive;

}



















