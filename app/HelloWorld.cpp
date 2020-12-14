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
	game->init();
	setUserData(game);
	setDrawFunction(draw);
	setUpdateFunction(update);
	startMessageLoop();
	destroyWindow();
	delete game;

	return 0;
}