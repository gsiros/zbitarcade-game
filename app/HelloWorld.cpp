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

#define MS_CAP 0.15f

using namespace graphics;

bool jump = false;

void draw() {

	Game* game = reinterpret_cast<Game*> (getUserData());
	game->draw();
}

void update(float ms) {

	Game* game = (Game*)getUserData();
	game->update();
	
}

int main() {
	Game* game = new Game();
	// GAME INIT
	game->init();
	setUserData(game);
	setDrawFunction(draw);
	setUpdateFunction(update);
	// END OF GAME INIT
	startMessageLoop();
	destroyWindow();
	delete game;

	return 0;
}