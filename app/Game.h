#pragma once
#include <string>
#include <list>
#include "Metrics.h"
#include "graphics.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Vect.h"

using namespace std;
using namespace graphics;

class Game : public Entity {
public:
	float timer;
	int score;
	float window_width = 800;
	float window_height = 500;

	Player player = Player(CHARACTER_WIDTH, CHARACTER_HEIGHT, CANVAS_WIDTH/2,CANVAS_HEIGHT - CHARACTER_HEIGHT / 2, 100, string(GOKU));
	Vect gravity = Vect(0, GRAVITY_PULL);

	list<Enemy *> enemy_list;

	Game();
	~Game();

	void init() override;
	void draw() override;
	void update() override;

};
