#include "Projectile.h"
#include <list>
using namespace std;
	
Projectile::Projectile(float width, float height, float center_x, float center_y, const string assetFile) {
	this->width = width;
	this->height = height;
	this->position = Vect(center_x, center_y);
	this->asset_projectile_left = assetFile + "_left.png";
	this->asset_projectile_right = assetFile + "_right.png";
	this->assetFile = asset_projectile_right;
}

Projectile::Projectile(const Projectile& p) {
	this->width = int(p.width);
	this->height = int(p.height);
	this->position = Vect(int(p.position.getX()), int(p.position.getY()));
	this->asset_projectile_left = string(p.asset_projectile_left);
	this->asset_projectile_right = string(p.asset_projectile_right);
	this->assetFile = string(p.assetFile);
}

float Projectile::getWidth() const {
	return this->width;
}

float Projectile::getHeight() const {
	return this->height;
}

string Projectile::getAssetFile() const {
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

void Projectile::move() {
	if (assetFile == asset_projectile_left) {
		position.setX(position.getX() - 3);
	} else {
		position.setX(position.getX() + 3);
	}
}

bool Projectile::keepProjectileInWindow(list<Projectile*> & projs,float windowWidth, float windowHeight) {
	if (position.getX() - getWidth() / 3 <= 0) {
		projs.remove(this);
		delete this;
		return true;
	}
	if (position.getX() + getWidth() / 3 > windowWidth) {
		projs.remove(this);
		delete this;
		return true;
	}
	return false;
}