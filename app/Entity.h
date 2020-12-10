#pragma once
class Entity {
	/*
	
		@gsiros:
		This is an abstract class for entities that live as the program runs.
		These can be the Game, Player, Enemy, Projectile, etc.
	
	*/
public:
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
};