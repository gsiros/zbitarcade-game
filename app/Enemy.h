#pragma once
#include "Character.h"
#include "Player.h"

class Enemy : public Character {
public:
	Enemy(float width, float height, float center_x, float center_y, float hp, const string assetFile) : Character(width, height, center_x, center_y, hp, assetFile) {}

	void init() = 0;
	void draw() = 0;
	void update() = 0;

	void attack() = 0;

	virtual void chasePlayer(Player* p) = 0;
};

