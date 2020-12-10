#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Vect.h"

class Game {
public:
	float window_width = 800;
	float window_height = 500;

	Player player = Player(80, 150, window_width - 40 / 2, window_height - 150 / 2, 100, "assets\\Goku");
	Enemy enemy = Enemy(80, 150, 0, window_height - 150 / 2, 100, "assets\\Piccolo");
	Vect gravity = Vect(0, 5);

	~Game() {

		for (list<Projectile*>::iterator it = player.projectile_list.begin(); it != player.projectile_list.end(); ++it) {
			delete* it;
		}
	}
};
