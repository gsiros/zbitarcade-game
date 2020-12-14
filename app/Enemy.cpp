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

	br.fill_opacity = 1;
	br.outline_width = 3;
	br.outline_opacity = 1;
	br.outline_color[0] = 0.f;
	br.outline_color[1] = 0.f;
	br.outline_color[2] = 0.f;
	br.fill_color[0] = 1.f;
	br.fill_color[1] = 0.f;
	br.fill_color[2] = 0.f;
	br.texture = "";
	drawRect(position.getX(), position.getY() - height/2 -20, 100, 10, br);
}

void Enemy::update()
{
	Game* game = reinterpret_cast<Game*>(getUserData());
	chasePlayer(&game->player);
	if(hp <= 0.f){
       	active = false;
		game->score++;
	}
}

void Enemy::chasePlayer(Player* p) {

	if(p->position.getX() > this->position.getX())
		this->setAssetFileMoveRight();

	if (p->position.getX() + 40 > this->position.getX()) {
		this->position.setX(this->position.getX() + (getDeltaTime()/10.f));
	}

	if(p->position.getX() < this->position.getX())
		this->setAssetFileMoveLeft();
	
	if (p->position.getX() - 40 < this->position.getX()) {
		this->position.setX(this->position.getX() - (getDeltaTime()/10.f));
		
	}

}