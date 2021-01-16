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

	PowerUp(float width, float height, float pos_x, float pos_y, const string & assetFile, Game* const game);
	void init() override;
	void draw() override;
	void update() override;
	
	void checkIfCaptured(Player * p);

	void setCaptured(bool captured) {
		this->captured = captured;
	}
	bool getCaptured() const {
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
	inline float getTimer() const {
		return this->timer;
	}
	inline float getWidth() const {
		return this->width;
	}
	inline float getHeight() const {
		return this->height;
	}


};

