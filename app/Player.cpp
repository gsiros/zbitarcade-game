#include "Player.h"



Player::Player(float center_x, float center_y){
		this->center_x = center_x;
		this->center_y = center_y;
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

void Player::setCenter_x(float cord_x) {
	center_x = cord_x;
}

void Player::setCenter_y(float cord_y) {
	center_y = cord_y;
}

float Player::getCenter_x() {
	return center_x;
}

float Player::getCenter_y() {
	return center_y;
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