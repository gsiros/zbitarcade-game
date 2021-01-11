#pragma once
#include <string>
#include <list>
#include "PowerUp.h"
#include "Metrics.h"
#include "graphics.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Vect.h"

using namespace std;
using namespace graphics;

enum GAMESTATE {
	MAIN_MENU, PLAYING, RETRY, CHOOSE_LEVEL, ABOUT_SCREEN
};

enum MAIN_MENU_BUTTON {
	PLAY, ABOUT, EXIT
};

enum RETRY_MENU_BUTTON {
	AGAIN, BACK_TO_MENU
};

enum LEVEL_SELECTION {
	BEACH, MOUNTAIN, NIGHT
};

class Game : public Entity {
public:

	int waveVariable = 8;

	GAMESTATE state = MAIN_MENU;
	MAIN_MENU_BUTTON buttonMM = PLAY;
	RETRY_MENU_BUTTON retry_choice = AGAIN;
	LEVEL_SELECTION level_button = BEACH;
	float arrow_offset;
	float button_timer;
	float timer;
	float timerLimit;
	int score;
	int prevScore;
	float window_width = 800;
	float window_height = 500;

	string level_asset;

	Player player = Player(CHARACTER_WIDTH -10, CHARACTER_HEIGHT, CANVAS_WIDTH/2,CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 200, string(GOKU_NEW));
	Vect gravity = Vect(0, GRAVITY_PULL);

	list<Enemy *> enemy_list;
	PowerUp* pu = nullptr;

	Game();
	~Game();

	void init() override;
	void draw() override;
	void update() override;

	void updateTimers();

	void clearCollections();
};
