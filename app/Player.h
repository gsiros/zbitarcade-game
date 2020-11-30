#pragma once
#include <string>
#include "Vect.h"

using namespace std;

/*		x
		___>
	y |
	  V

*/

class Player
{
private:
	float center_x, center_y;
	float width, height;
	float hp;
	string asset_file;

public:
	Vect position;
	Vect velocity;

	Player(float center_x, float center_y);

	float getWidth();
	float getHeight();
	float getHp();
	string getAssetFile();
	void setAssetFile(string const name);

};

