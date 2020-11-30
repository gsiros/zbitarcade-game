#include <iostream>
#include <graphics.h>
#include "Player.h"

using namespace graphics;

class Game {
public:
	float window_width = 800;
	float window_height = 500;

	Player player = Player(window_width/2, window_height/2);
};

void drawPlayer() {

	Game* userData = (Game*)getUserData();
	
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = userData->player.getAssetFile();
	drawRect(userData->player.getCenter_x(),userData->player.getCenter_y(), userData->player.getWidth(), userData->player.getHeight(), br);
}

void draw() {
	drawPlayer();
}

void update(float ms) {

	Game* userData = (Game*)getUserData();

	// If 'W' is pressed:
	if (getKeyState(SCANCODE_W)) {
		userData->player.setCenter_y(userData->player.getCenter_y() - 1);	
	}

	// If 'S' is pressed:
	if (getKeyState(SCANCODE_S)) {
		userData->player.setCenter_y(userData->player.getCenter_y() + 1);
	}

	// If 'A' is pressed:
	if (getKeyState(SCANCODE_A)) {
		userData->player.setCenter_x(userData->player.getCenter_x() - 1);
	}

	// If 'D' is pressed:
	if (getKeyState(SCANCODE_D)) {
		userData->player.setCenter_x(userData->player.getCenter_x() + 1);
	}
	
	
}

int main() {
	Game* game = new Game();
	createWindow(game->window_width, game->window_height, "Demo");
	setUserData(game);
	setDrawFunction(draw);
	setUpdateFunction(update);
	startMessageLoop();
	destroyWindow();
	return 0;
}