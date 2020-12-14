#include "Game.h"
#include "Metrics.h"
#include "graphics.h"
#include <math.h>
#include <random>

using namespace graphics;

Game::Game()
{
}
Game::~Game() {

	for (list<Projectile*>::iterator it = player.projectile_list.begin(); it != player.projectile_list.end(); ++it) {
		delete* it;
	}
	for (list<Enemy *>::iterator it = enemy_list.begin(); it != enemy_list.end(); ++it) {
		delete* it;
	}

}

void Game::init() {
	timer = 0.f;
	// DO NOT CHANGE TO CANVAS_WIDTH/_HEIGHT
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo");
	setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	setCanvasScaleMode(CANVAS_SCALE_FIT);
	player.init();
}

void Game::draw()
{
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "assets\\background.png";
	drawRect((CANVAS_WIDTH)/ 2, (CANVAS_HEIGHT) / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	// Draw Entities:
	for(list<Enemy *>::iterator it = enemy_list.begin(); it!=enemy_list.end(); ++it){
		(*it)->draw();
	}
	player.draw();
	

}

void Game::update()
{	

	if(getGlobalTime()>2000 && timer > 3000){
		enemy_list.push_back(new Enemy(CHARACTER_WIDTH, CHARACTER_HEIGHT, (rand() % 2)*CANVAS_WIDTH , CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 200, string(PICCOLO)));
		timer = 0.f;
	}
	for(list<Enemy *>::iterator it = enemy_list.begin(); it!=enemy_list.end(); ++it){
		if(*it != nullptr){
			if((*it)->getActiveStatus()){
				(*it)->update();
			} else {
				it = enemy_list.erase(it);
				if (it == enemy_list.end())
					break;
			}
		}	
	}
	player.update();
	timer += getDeltaTime();
}
