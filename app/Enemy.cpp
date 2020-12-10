#include "Game.h"
#include "Enemy.h"
#include "graphics.h"

using namespace graphics;

void Enemy::init()
{
}

void Enemy::draw()
{
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = assetFile;
	drawRect(position.getX(), position.getY(), width, height, br);

}

void Enemy::update()
{
	Game* game = reinterpret_cast<Game*>(getUserData());
	chasePlayer(&game->player);
}

void Enemy::chasePlayer(Player* p) {

	if(p->position.getX() > this->position.getX())
		this->setAssetFileMoveRight();

	if (p->position.getX() + 40 > this->position.getX()) {
		this->position.setX(this->position.getX() + 0.6);
		
	}

	if(p->position.getX() < this->position.getX())
		this->setAssetFileMoveLeft();
	
	if (p->position.getX() - 40 < this->position.getX()) {
		this->position.setX(this->position.getX() - 0.6);
		
	}

}