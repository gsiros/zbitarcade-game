#include <iostream>
#include <graphics.h>
#include <string>
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Vect.h"
#include <list>

#define MS_CAP 0.15f

using namespace graphics;

bool jump = false;

class Game {
public:
	float window_width = 800;
	float window_height = 500;

	Player player = Player (80,150,window_width - 40/2, window_height - 150/2, 100,"assets\\Goku");
	Enemy enemy = Enemy(80, 150, 0, window_height - 150/2, 100, "assets\\Piccolo");
	Vect gravity = Vect(0, 5);

	~Game() {
		
		for (list<Projectile*>::iterator it = player.projectile_list.begin(); it != player.projectile_list.end(); ++it) {
			delete* it;
		}
	}
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
	for (list<Projectile*>::iterator it = userData->player.projectile_list.begin(); it != userData->player.projectile_list.end(); ++it) {
		if (*it != nullptr) {
			br.texture = (*it)->getAssetFile();
			drawRect((*it)->position.getX(),(*it)->position.getY(), (*it)->getWidth(), (*it)->getHeight(), br);
		}	
	}
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
		userData->player.position = userData->player.position + userData->player.velocity * MS_CAP;
		userData->player.velocity = userData->player.velocity + userData->gravity * MS_CAP;
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

	// If "SPACEBAR" is pressed:
	if (getKeyState(SCANCODE_SPACE)) {
		if(userData->player.projectile_list.empty()) {
			playSound("assets\\sounds\\fireball_sound_effect.mp3",0.1f, false);
			userData->player.attack();
			
		} else if (abs(userData->player.projectile_list.back()->position.getX() - userData->player.position.getX()) > 50) {
			playSound("assets\\sounds\\fireball_sound_effect.mp3",0.1f, false);
			userData->player.attack();
		}
	}

	for (list<Projectile*>::iterator it = userData->player.projectile_list.begin(); it != userData->player.projectile_list.end(); ++it) {
		if (*it != nullptr) {
			(*it)->move();
		}		
	}

	for (list<Projectile*>::iterator it = userData->player.projectile_list.begin(); it != userData->player.projectile_list.end(); ++it) {
		if (*it != nullptr) {
			// Check if projectile collided with walls;
			if ((*it)->keepProjectileInWindow(userData->player.projectile_list, userData->window_width, userData->window_height)) {
				break;
			}
			
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
	delete game;
	return 0;
}