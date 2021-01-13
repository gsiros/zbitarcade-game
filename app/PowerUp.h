#pragma once
#include "Game.h"
#include <string>
#include "Entity.h"
#include "Player.h"

using namespace std;

class PowerUp : public Entity {
protected:
	bool captured;
	float timer;
	float width;
	float height;
	string assetFile;

public:
	Vect position;

	PowerUp(float width, float height, float pos_x, float pos_y, string assetFile, Game* const game);
	void init() override;
	void draw() override;
	void update() override;
	
	void checkIfCaptured(Player * p);

	void setCaptured(bool captured) {
		this->captured = captured;
	}
	bool getCaptured() {
		return this->captured;
	}
	void setWidth(float width) {
		this->width = width;
	}
	void setHeight(float height) {
		this->height = height;
	}

	void setTimer(float ms) {
		this->timer = ms;
	}
	inline float getTimer() {
		return this->timer;
	}
	inline float getWidth() {
		return this->width;
	}
	inline float getHeight() {
		return this->height;
	}


};

