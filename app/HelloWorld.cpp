#include <graphics.h>
#include "Game.h"

using namespace graphics;

int main() {
	Game* game = new Game();
	
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ZBIT ARCADE");
	setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	setCanvasScaleMode(CANVAS_SCALE_FIT);
	setFullScreen(true);
	setUserData(game);
	setDrawFunction(bind(&Game::draw, game));
	setUpdateFunction(bind(&Game::update, game));
	game->init();
	startMessageLoop();
	destroyWindow();
	delete game;
	return 0;
}