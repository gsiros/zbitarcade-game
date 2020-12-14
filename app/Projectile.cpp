#include "Projectile.h"
#include <list>
#include "Game.h"
#include "graphics.h"
#include <iostream>
using namespace std;
using namespace graphics;

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

void Projectile::init()
{
}

void Projectile::draw()
{
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = assetFile;
	drawRect(position.getX(), position.getY(), width, height, br);

}

void Projectile::update()
{
	move();
	keepInBounds();
	checkCollisionWithEnemy();
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
		position.setX(position.getX() - (getDeltaTime() / 2.f));
	}
	else {
		position.setX(position.getX() + (getDeltaTime() / 2.f));
	}
}

void Projectile::keepInBounds()
{
	if (position.getX() - width / 3 <= 0 || position.getX() + getWidth() / 3 > CANVAS_WIDTH) {
		active = false;
	}
}

void Projectile::checkCollisionWithEnemy() {
	list<Enemy*> enemies = reinterpret_cast<Game*>(getUserData())->enemy_list;
	for (list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		// Check if collided with enemy:
		if ((abs((*it)->position.getX() - position.getX()) < 30) && (abs((*it)->position.getY() - position.getY()) < (*it)->getHeight()/2)) {
			// lower hp of enemy:
			(*it)->setHp((*it)->getHp() - 25.f);
			active = false;
		}
	}
}