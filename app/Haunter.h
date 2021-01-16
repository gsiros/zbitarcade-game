#pragma once
#include "Game.h"
#include "Enemy.h"
class Haunter : public Enemy {
public:
	Haunter(float width, float height, float center_x, float center_y, float hp, const string & assetFile, Game* const game) : Enemy(width, height, center_x, center_y, hp, assetFile, game) {}

	void init() override;
	void draw() override;
	void update() override;

	void attack() override;

	void chasePlayer(const Player* const p) override;
};

