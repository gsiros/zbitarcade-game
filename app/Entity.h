#pragma once
#include "Game.h"
class Entity {
	/*

		This is an abstract class for entities that live as the program runs.
		These can be the Game, Player, Enemy, Projectile, etc.
	
	*/
protected:
	class Game* const game;
	bool active = true;
public:

	Entity(Game* const game);

	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;

	inline bool getActiveStatus() const {return active;}
	void setActiveStatus(bool status) {active = status;}
};