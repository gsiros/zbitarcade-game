#pragma once
#include <string>
#include <list>
#include "Character.h"
#include "Vect.h"
#include "Projectile.h"

using namespace std;

/*		x
		___>
	y |
	  V

*/

class Player : public Character {
private:
	bool jump;
public:
	Player(float width, float height, float center_x, float center_y, float hp, const string assetFile) : Character(width, height, center_x, center_y, hp, assetFile) {}
	
	void init() override;
	void draw() override;
	void update() override;
	
	void attack() override;
	list<Projectile*> projectile_list;
};

