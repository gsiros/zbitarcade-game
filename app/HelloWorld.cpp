#include <iostream>
#include <graphics.h>
#include "Player.h"

using namespace graphics;

bool jump = false;

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
	Game* userData = (Game*)getUserData();
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "assets\\background.png";
	drawRect(userData->window_width/2,userData->window_height/2, userData->window_width, userData->window_height, br);

	drawPlayer();
}

void update(float ms) {

	Game* userData = (Game*)getUserData();
	/*if (userData->player.getCenter_y() + userData->player.getHeight() / 2 < userData->window_height)
		userData->player.setCenter_y(userData->player.getCenter_y() + 0.01f * userData->player.getCenter_y());
	else
		userData->player.setCenter_y(userData->window_height - userData->player.getHeight()/2);
	*/
	// If 'SPACE' is pressed:
	if (getKeyState(SCANCODE_SPACE)) {
		jump = true;
	}

	if (jump) {
	// y_{n+1} = y_{n} - 0.01*y^2_{n}
		userData->player.setCenter_y((userData->player.getCenter_y()) - 0.01f*(userData->player.getCenter_y())*(userData->player.getCenter_y()));
		if (userData->player.getCenter_y() + userData->player.getHeight() / 2 > userData->window_height) {
			jump = false;
			userData->player.setCenter_y((userData->window_height - userData->player.getHeight()/2));
		}
	}

	// If 'W' is pressed:
	if (getKeyState(SCANCODE_W)) {
		if (userData->player.getCenter_y() - userData->player.getHeight()/2 > 0)
			userData->player.setCenter_y(userData->player.getCenter_y() - 2);	
	}

	// If 'S' is pressed:
	if (getKeyState(SCANCODE_S)) {
		if (userData->player.getCenter_y() + userData->player.getHeight()/2< userData->window_height)
			userData->player.setCenter_y(userData->player.getCenter_y() + 1);
	}

	// If 'A' is pressed:
	if (getKeyState(SCANCODE_A)) {
		if (userData->player.getCenter_x() - userData->player.getWidth()/3 > 0)
			userData->player.setCenter_x(userData->player.getCenter_x() - 1);
	}

	// If 'D' is pressed:
	if (getKeyState(SCANCODE_D)) {
		if (userData->player.getCenter_x() + userData->player.getWidth()/3 < userData->window_width)
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