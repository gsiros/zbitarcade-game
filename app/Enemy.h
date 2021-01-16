#pragma once
#include "Character.h"
#include "Player.h"

class Enemy : public Character {
public:
	Enemy(float width, float height, float center_x, float center_y, float hp, const string & assetFile, Game* const game);

	void init() = 0;
	void draw() = 0;
	void update() = 0;

	virtual void attack() = 0;

	virtual void chasePlayer(const Player* const p) = 0;
};

