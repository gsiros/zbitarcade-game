#pragma once
#include "Game.h"
#include <string>
#include "Vect.h"
#include "Character.h"
#include <list>
#include "Entity.h"
using namespace std;

class Projectile : public Entity {
protected:
	float width, height;
	string assetFile;
	string asset_projectile_left;
	string asset_projectile_right;

public:
	Vect position, velocity;

	Projectile(float width, float height, float center_x, float center_y, const string assetFile, Game* const game);
	//Projectile(const Projectile& p);

	void init() override;
	void draw() override;
	void update() override;

	float getWidth() const;
	float getHeight() const;
	string getAssetFile() const;
	void setAssetFile(string const name);
	void setAssetFileMoveRight();
	void setAssetFileMoveLeft();
	void move();
	void keepInBounds();
	void checkCollisionWithEnemy();
};

