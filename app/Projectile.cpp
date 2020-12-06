#include "Projectile.h"
	
Projectile::Projectile(float width, float height, float center_x, float center_y, const string assetFile) {
	this->width = width;
	this->height = height;
	this->position = Vect(center_x, center_y);
	this->asset_projectile_left = assetFile + "_left.png";
	this->asset_projectile_right = assetFile + "_right.png";
	this->assetFile = asset_projectile_left;
}

float Projectile::getWidth() {
	return this->width;
}

float Projectile::getHeight() {
	return this->height;
}

string Projectile::getAssetFile() {
	return this->assetFile;
}

void Projectile::setAssetFile(string const name) {
	this->assetFile = name;
}

void Projectile::setAssetFileMoveRight() {
	this->assetFile = asset_projectile_right;
}

void Projectile::setAssetFileMoveLeft() {
	this->assetFile = asset_projectile_left;
}