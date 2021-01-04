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
	MAIN_MENU, PLAYING, RETRY
};

enum MAIN_MENU_BUTTON {
	PLAY, ABOUT, EXIT
};

class Game : public Entity {
public:

	int waveVariable = 5;

	GAMESTATE state = MAIN_MENU;
	MAIN_MENU_BUTTON buttonMM = PLAY;
	float arrow_offset;
	float button_timer;
	float timer;
	float timerLimit;
	int score;
	int prevScore;
	float window_width = 800;
	float window_height = 500;

	Player player = Player(CHARACTER_WIDTH, CHARACTER_HEIGHT, CANVAS_WIDTH/2,CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 200, string(GOKU));
	Vect gravity = Vect(0, GRAVITY_PULL);

	list<Enemy *> enemy_list;
	PowerUp* pu = nullptr;

	Game();
	~Game();

	void init() override;
	void draw() override;
	void update() override;

	void updateTimers();
};
