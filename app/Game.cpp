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
}

void Game::init() {
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo");
	player.init();
}

void Game::draw()
{
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "assets\\background.png";
	drawRect(WINDOW_WIDTH/ 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);

	// Draw Entities:
	enemy.draw();
	player.draw();
	

}

void Game::update()
{
	enemy.update();
	player.update();

}
