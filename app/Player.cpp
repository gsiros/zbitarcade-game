#include "Player.h"



Player::Player(float center_x, float center_y){
		this->center_x = center_x;
		this->center_y = center_y;
		position = Vect(center_x, center_y);
		velocity = Vect(0, -40);
		width = 80.0f;
		height = 150.0f;
		hp = 100.0f;
		setAssetFile("assets\\Goku1.png");
}

string Player::getAssetFile() {
	return asset_file;
}

void Player::setAssetFile(const string name){
	asset_file = name;
}

float Player::getHp() {
	return hp;
}


float Player::getHeight() {
	return height;
}

float Player::getWidth() {
	return width;
}