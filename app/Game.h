#pragma once
#include <string>
#include <list>
#include "Metrics.h"
#include "Vect.h"
#include <graphics.h>

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

class Game{
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

	class Player* player;
	Vect gravity = Vect(0, GRAVITY_PULL);

	list<class Enemy *> enemy_list;
	class PowerUp* pu = nullptr;

	Game();
	~Game();

	void init();
	void draw();
	void update();

	void updateTimers();

	void clearCollections();
};
