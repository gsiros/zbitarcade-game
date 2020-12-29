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
	bool upgraded;
	float attackSpeed;
	float movementSpeed;
	float duration;
public:
	Player(float width, float height, float center_x, float center_y, float hp, const string assetFile) : Character(width, height, center_x, center_y, hp, assetFile) {}
	
	void init() override;
	void draw() override;
	void update() override;
	
	void attack() override;
	list<Projectile*> projectile_list;

	void setJump(bool status);
	bool getJump();
	void upgrade(float duration, float attackSpeed, float movementSpeed);
	inline float getAttackSpeed() {
		return this->attackSpeed;
	}
	void setAttackSpeed(float attackSpeed) {
		this->attackSpeed = attackSpeed;
	}
	void setMovementSpeed(float movementSpeed) {
		this->movementSpeed = movementSpeed;
	}
	inline float getMovementSpeed() {
		return this->movementSpeed;
	}
	void setUpgraded(bool flag) {
		this->upgraded = flag;
	}
	inline float getUpgraded() {
		return this->upgraded;
	}

};

