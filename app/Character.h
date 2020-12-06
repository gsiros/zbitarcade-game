#pragma once
#include <string>
#include "Vect.h"
using namespace std;

class Character {

protected:
	float width, height;
	float hp;
	string assetFile;
	string asset_character_left;
	string asset_character_right;

public:
	Vect position, velocity;

	Character(float width, float height, float center_x, float center_y, float hp, const string assetFile);

	float getWidth();
	float getHeight();
	float getHp();
	string getAssetFile();
	void setAssetFile(string const name);
	void setAssetFileMoveRight();
	void setAssetFileMoveLeft();	

};


