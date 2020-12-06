#include <iostream>
#include <graphics.h>
#include <string>
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Vect.h"
#include <list>

using namespace graphics;

bool jump = false;

class Game {
public:
	float window_width = 800;
	float window_height = 500;

	Player player = Player (80,150,window_width - 40/2, window_height - 150/2, 100,"assets\\Goku");
	Enemy enemy = Enemy(80, 150, 0, window_height - 150/2, 100, "assets\\Piccolo");
	Projectile proj = Projectile(40,40,window_width/2,window_height/2, "assets\\Haduken");
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

void drawEnemy() {
	Game* userData = (Game*)getUserData();
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = userData->enemy.getAssetFile();
	drawRect(userData->enemy.position.getX(), userData->enemy.position.getY(), userData->enemy.getWidth(), userData->enemy.getHeight(), br);
}

void drawProjectile() {
	Game* userData = (Game*)getUserData();
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = userData->proj.getAssetFile();
	drawRect(userData->proj.position.getX(),userData->proj.position.getY(), userData->proj.getWidth(), userData->proj.getHeight(), br);
}

void draw() {
	Game* userData = (Game*)getUserData();
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "assets\\background.png";
	drawRect(userData->window_width/2,userData->window_height/2, userData->window_width, userData->window_height, br);
	drawEnemy();
	drawPlayer();
	drawProjectile();
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
		if (userData->player.position.getX() - userData->player.getWidth() / 3 > 0) {
			userData->player.position.setX(userData->player.position.getX() - 1.5);
			userData->player.setAssetFileMoveLeft();
		}
	}

	// If 'D' is pressed:
	if (getKeyState(SCANCODE_D)) {
		if (userData->player.position.getX() + userData->player.getWidth() / 3 < userData->window_width) {
			userData->player.position.setX(userData->player.position.getX() + 1.5);
			userData->player.setAssetFileMoveRight();
		}
	}
	
	if (userData->player.position.getY() + userData->player.getHeight() / 2 >= userData->window_height)
	{
		userData->player.position.setY(userData->window_height - userData->player.getHeight() / 2);
		jump = false;
		userData->gravity = Vect(0,5);
		userData->player.velocity = Vect(0,-40);
	}
	
	userData->enemy.chasePlayer(&userData->player);
	
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