#include "Enemy.h"

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