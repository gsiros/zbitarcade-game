#pragma once
#include <string>
#include "Vect.h"
#include "Character.h"

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

	float getWidth();
	float getHeight();
	string getAssetFile();
	void setAssetFile(string const name);
	void setAssetFileMoveRight();
	void setAssetFileMoveLeft();
};

