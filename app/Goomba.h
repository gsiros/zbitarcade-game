#pragma once
#include "Game.h"
#include "Enemy.h"
class Goomba : public Enemy {
public:
	Goomba(float width, float height, float center_x, float center_y, float hp, const string & assetFile, Game* const game);

	void init() override;
	void draw() override;
	void update() override;

	void attack() override;

	void chasePlayer(const Player* const p) override;
	void checkIfSteppedOn();

};

