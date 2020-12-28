#include "Game.h"
#include "Haunter.h"
#include "Piccolo.h"
#include "Metrics.h"
#include "graphics.h"
#include <math.h>
#include <random>
#include "Zombie.h"
#include "Goomba.h"
#include "Jason.h"

using namespace graphics;

Game::Game()
{
}
Game::~Game() {

	for (list<Projectile*>::iterator it = player.projectile_list.begin(); it != player.projectile_list.end(); ++it) {
		delete *it;
	}
	for (list<Enemy *>::iterator it = enemy_list.begin(); it != enemy_list.end(); ++it) {
		delete *it;
	}

}

void Game::init() {
	timer = 0.f;
	score = 0;
	// DO NOT CHANGE TO CANVAS_WIDTH/_HEIGHT
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo");
	setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	setCanvasScaleMode(CANVAS_SCALE_FIT);
	//setFullScreen(true);
	setFont(string(POCOYO_TV_FONT));
	playMusic(string(JOJOS_MAIN_MUSIC), 0.05f);
	player.init();
}

void Game::draw()
{
	// background
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "assets\\background.png";
	drawRect((CANVAS_WIDTH)/ 2, (CANVAS_HEIGHT) / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	// Score text
	br.texture = "";
	br.fill_color[0] = .0f;
	br.fill_color[1] = .0f;
	br.fill_color[2] = .0f;
	drawText(160, 50, 30, "Score: "+to_string(score), br);

	// Goku player picture
	Brush br1;
	br1.fill_opacity = 1;
	br1.outline_opacity = 0;
	br1.texture = string(GOKU_PROFILE_PIC);
	drawRect(65, 57, 75, 75, br1);

	// UI Hp bar
	float player_hp = (player.getHp() > 0) ? player.getHp() : 0;
	Brush br3;
	br3.fill_opacity = 1;
	br3.fill_color[0] = 0.f + (200-player_hp)/200; // RED
	br3.fill_color[1] = 1.f - (200-player_hp)/200; // GREEN
	br3.fill_color[2] = 0.f; // BLUE
	br3.texture = "";


	drawRect(236 - (((200-player_hp)/200)*205/2), 75, (player_hp/200)*205, 27, br3);

	// Player UI
	Brush br2;
	br2.fill_opacity = 1;
	br2.outline_opacity = 0;
	br2.texture = string(PLAYER_UI);
	drawRect(180, 60, 360, 100, br2);

	// Draw Entities:
	for(list<Enemy *>::iterator it = enemy_list.begin(); it!=enemy_list.end(); ++it){
		(*it)->draw();
	}
	if (player.getActiveStatus()) {
		player.draw();
	}
		
}

void Game::update()
{	
	if (player.getActiveStatus()) {
		if (getGlobalTime() > 2000 && timer > 5000) {

			int choice = rand() % 5;

			switch (choice) {

			case 0:
				enemy_list.push_back(new Piccolo(CHARACTER_WIDTH, CHARACTER_HEIGHT, (rand() % 2) * CANVAS_WIDTH, CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 100, string(PICCOLO)));
				break;
			case 1:
				enemy_list.push_back(new Zombie(CHARACTER_WIDTH, CHARACTER_HEIGHT, (rand() % 2) * CANVAS_WIDTH, CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 200, string(ZOMBIE)));
				break;
			case 2:
				enemy_list.push_back(new Haunter(80, 80, (rand() % 2) * CANVAS_WIDTH, CANVAS_HEIGHT - CHARACTER_HEIGHT / 2 - 50, 100, string(HAUNTER)));
				break;
			case 3:
				enemy_list.push_back(new Goomba(60, 60, (rand() % 2) * CANVAS_WIDTH, CANVAS_HEIGHT - 25, 25, string(GOOMBA)));
				break;
			case 4:
				enemy_list.push_back(new Jason(CHARACTER_WIDTH, CHARACTER_HEIGHT, (rand() % 2) * CANVAS_WIDTH, CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 100, string(JASON)));

				break;
			}

			enemy_list.back()->init();
			timer = 0.f;
		}

		for (list<Enemy*>::iterator it = enemy_list.begin(); it != enemy_list.end(); ++it) {
			if (*it != nullptr) {
				if ((*it)->getActiveStatus()) {
					(*it)->update();
				}
				else {
					delete* it;
					it = enemy_list.erase(it);
					if (it == enemy_list.end())
						break;
				}
			}
		}
		player.update();
		timer += getDeltaTime();
	}
	else {

	}
}
