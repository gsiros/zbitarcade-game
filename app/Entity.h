#pragma once
class Entity {
	/*

		This is an abstract class for entities that live as the program runs.
		These can be the Game, Player, Enemy, Projectile, etc.
	
	*/
protected:
	bool active = true;
public:
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;

	inline bool getActiveStatus() {return active;}
	void setActiveStatus(bool status) {active = status;}
};