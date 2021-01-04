#include <iostream>
#include <graphics.h>
#include <string>
#include "Game.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Vect.h"
#include <list>

using namespace graphics;

bool jump = false;

void draw() {

	Game* game = reinterpret_cast<Game*>(getUserData());
	game->draw();
}

void update(float ms) {

	Game* game = reinterpret_cast<Game*>(getUserData());
	game->update();
	
}

int main() {
	Game* game = new Game();
	
	// DO NOT CHANGE TO CANVAS_WIDTH/_HEIGHT
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo");
	setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	setCanvasScaleMode(CANVAS_SCALE_FIT);
	//setFullScreen(true);
	setUserData(game);
	setDrawFunction(draw);
	setUpdateFunction(update);
	game->init();
	startMessageLoop();
	destroyWindow();
	delete game;

	return 0;
}