#include "Game.h"
#include "Metrics.h"
#include "graphics.h"

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
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo");
	player.init();
	enemy_list.push_back(new Enemy(CHARACTER_WIDTH, CHARACTER_HEIGHT, 0, WINDOW_HEIGHT - CHARACTER_HEIGHT / 2, 100, string(PICCOLO)));
}

void Game::draw()
{
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "assets\\background.png";
	drawRect(WINDOW_WIDTH/ 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);

	// Draw Entities:
	//enemy.draw();
	for(list<Enemy *>::iterator it = enemy_list.begin(); it!=enemy_list.end(); ++it){
		(*it)->draw();
	}
	player.draw();
	

}

void Game::update()
{
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
}
