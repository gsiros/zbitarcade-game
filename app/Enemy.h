#pragma once
#include "Character.h"
#include "Player.h"

class Enemy : public Character {
public:
	Enemy(float width, float height, float center_x, float center_y, float hp, const string assetFile) : Character(width, height, center_x, center_y, hp, assetFile) {}

	void chasePlayer(Player * p);
};

