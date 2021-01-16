#pragma once
#include "Game.h"
#include <string>
#include "Vect.h"
#include "Entity.h"
using namespace std;

class Character : public Entity {

protected:
	float attackTimer;
	float width, height;
	float hp;
	string assetFile;
	string asset_character_left;
	string asset_character_right;

public:
	Vect position, velocity;

	Character(float width, float height, float center_x, float center_y, float hp, const string & assetFile, Game* const game);

	void init() = 0;
	void draw() = 0;
	void update() = 0;

	virtual void attack() = 0;

	float getWidth() const;
	float getHeight() const;
	float getHp() const;
	string getAssetFile() const;
	void setHp(float hpPoints);
	void setAssetFile(const string & name);
	void setAssetFileMoveRight();
	void setAssetFileMoveLeft();	

};


