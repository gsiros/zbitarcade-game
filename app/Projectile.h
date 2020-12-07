#pragma once
#include <string>
#include "Vect.h"
#include "Character.h"
#include <list>
using namespace std;

class Projectile {
protected:
	float width, height;
	string assetFile;
	string asset_projectile_left;
	string asset_projectile_right;

public:
	Vect position, velocity;

	Projectile(float width, float height, float center_x, float center_y, const string assetFile);
	Projectile(const Projectile& p);
	float getWidth() const;
	float getHeight() const;
	string getAssetFile() const;
	void setAssetFile(string const name);
	void setAssetFileMoveRight();
	void setAssetFileMoveLeft();
	void move();
	bool keepProjectileInWindow(list<Projectile*> & projs, float windowWidth, float windowHeight);
};

