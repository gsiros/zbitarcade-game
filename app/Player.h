#pragma once
#include "Game.h"
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
	Player(float width, float height, float center_x, float center_y, float hp, const string assetFile, Game* const game) : Character(width, height, center_x, center_y, hp, assetFile, game) {}
	~Player();
	void init() override;
	void draw() override;
	void update() override;
	
	void attack() override;
	list<class Projectile*> projectile_list;

	void setJump(bool status);
	bool getJump();
	void upgrade(float duration, float attackSpeed, float movementSpeed, string assetFile);
	
	inline float getAttackSpeed() const {
		return this->attackSpeed;
	}
	void setAttackSpeed(float attackSpeed) {
		this->attackSpeed = attackSpeed;
	}
	void setMovementSpeed(float movementSpeed) {
		this->movementSpeed = movementSpeed;
	}
	inline float getMovementSpeed() const {
		return this->movementSpeed;
	}
	void setUpgraded(bool flag) {
		this->upgraded = flag;
	}
	inline float getUpgraded() const {
		return this->upgraded;
	}
	inline float getUpgradeDuration() const { return this->duration; }

};

