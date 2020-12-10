#pragma once
#include "Metrics.h"
#include "graphics.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Vect.h"

using namespace graphics;

class Game : public Entity {
public:
	float window_width = 800;
	float window_height = 500;

	Player player = Player(80, 150, window_width - 40 / 2, window_height - 150 / 2, 100, "assets\\Goku");
	Enemy enemy = Enemy(80, 150, 0, window_height - 150 / 2, 100, "assets\\Piccolo");
	Vect gravity = Vect(0, 5);

	Game();
	~Game();

	void init() override;
	void draw() override;
	void update() override;

};
