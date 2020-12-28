#pragma once
#include "Enemy.h"
class Goomba : public Enemy {
public:
	Goomba(float width, float height, float center_x, float center_y, float hp, const string assetFile) : Enemy(width, height, center_x, center_y, hp, assetFile) {}

	void init() override;
	void draw() override;
	void update() override;

	void attack() override;

	void chasePlayer(Player* p) override;
	void checkIfSteppedOn();

};

