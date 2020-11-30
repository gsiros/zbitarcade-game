#include <iostream>
#include <graphics.h>
#include "Player.h"
#include "Vect.h"

using namespace graphics;

bool jump = false;

class Game {
public:
	float window_width = 800;
	float window_height = 500;

	Player player = Player(window_width/2, window_height/2);

	Vect gravity = Vect(0, 5);
};

void drawPlayer() {

	Game* userData = (Game*)getUserData();
	
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = userData->player.getAssetFile();
	drawRect(userData->player.position.getX(),userData->player.position.getY(), userData->player.getWidth(), userData->player.getHeight(), br);
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
	

	// If 'W' is pressed:
	if (getKeyState(SCANCODE_W)) {
		jump = true;
	}

	if (jump) {
		userData->player.position = userData->player.position + userData->player.velocity * 0.15f;
		userData->player.velocity = userData->player.velocity + userData->gravity * 0.15f;
	}

	// If 'S' is pressed:
	if (getKeyState(SCANCODE_S)) {
		if (userData->player.position.getY() + userData->player.getHeight() / 2 < userData->window_height)
			userData->player.position.setY(userData->player.position.getY() + 2);
		else {
			userData->player.position.setY(userData->window_height - userData->player.getHeight() / 2);
		}
			
	}

	// If 'A' is pressed:
	if (getKeyState(SCANCODE_A)) {
		if (userData->player.position.getX() - userData->player.getWidth() / 3 > 0)
			userData->player.position.setX(userData->player.position.getX() - 1.5);
	}

	// If 'D' is pressed:
	if (getKeyState(SCANCODE_D)) {
		if (userData->player.position.getX() + userData->player.getWidth()/3 < userData->window_width)
			userData->player.position.setX(userData->player.position.getX() + 1.5);
	}
	
	if (userData->player.position.getY() + userData->player.getHeight() / 2 >= userData->window_height)
	{
		userData->player.position.setY(userData->window_height - userData->player.getHeight() / 2);
		jump = false;
		userData->gravity = Vect(0,5);
		userData->player.velocity = Vect(0,-40);
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