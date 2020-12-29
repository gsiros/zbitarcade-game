#include <string>
#include "PowerUp.h"
#include "Game.h"

using namespace std;

PowerUp::PowerUp(float width, float height, float pos_x, float pos_y, string assetFile) : width(width), height(height), position(pos_x, pos_y) {
	this->assetFile = assetFile + ".png";
	this->active = true;
	this->captured = false;
}

void PowerUp::init() {
	this->timer = 6000;
}

void PowerUp::draw() {
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = assetFile;
	drawRect(position.getX(), position.getY(), width, height, br);
}

void PowerUp::update() {

	Game* g = reinterpret_cast<Game*>(getUserData());

	this->timer -= getDeltaTime();

	if(!captured)
		checkIfCaptured(&g->player);

	if (timer <= 0) {
		setActiveStatus(false);
	}
}

void PowerUp::checkIfCaptured(Player* p) {
	if (sqrt(pow(position.getX() - p->position.getX(),2) + pow(position.getY() - p->position.getY(),2)) < width / 2) {
		captured = true;
		p->upgrade(10000, 200, 3);
	}
}