#include "Goomba.h"
#include "graphics.h"
#include "Metrics.h"
#include "Game.h"

using namespace graphics;

void Goomba::init()
{
	attackTimer = 0;
}

void Goomba::draw()
{
	// Draw player 
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = assetFile;
	drawRect(position.getX(), position.getY(), width, height, br);

	// Draw Health Bar :

	// Inner rectangle
	br.fill_opacity = 1;
	br.fill_color[0] = 1.f;
	br.fill_color[1] = 0.f;
	br.fill_color[2] = 0.f;
	br.texture = "";
	drawRect(position.getX() - (((25 - hp) / 25) * 100 / 2), position.getY() - height / 2 - 20, (hp / 25) * 100, 10, br);

	//Outer rectangle
	Brush br1;
	br1.fill_opacity = 0;
	br1.outline_width = 3;
	br1.outline_opacity = 1;
	br1.outline_color[0] = 0.f;
	br1.outline_color[1] = 0.f;
	br1.outline_color[2] = 0.f;
	drawRect(position.getX(), position.getY() - height / 2 - 20, 100, 10, br1);
}

void Goomba::update()
{
	Game* game = reinterpret_cast<Game*>(getUserData());
	chasePlayer(&game->player);
	attack();
	checkIfSteppedOn();
	if (hp <= 0.f) {
		active = false;
		game->score++;
	}
	if (attackTimer < 1500) {
		attackTimer += getDeltaTime();
	}
	else {
		attackTimer = 1500;
	}
}

void Goomba::chasePlayer(Player* p) {

	if (p->position.getX() > this->position.getX())
		this->setAssetFileMoveRight();

	if (p->position.getX() + 40 > this->position.getX()) {
		this->position.setX(this->position.getX() + (getDeltaTime() / 30.f));
	}

	if (p->position.getX() < this->position.getX())
		this->setAssetFileMoveLeft();

	if (p->position.getX() - 40 < this->position.getX()) {
		this->position.setX(this->position.getX() - (getDeltaTime() / 30.f));

	}
}

void Goomba::attack() {
	Game* g = reinterpret_cast<Game*>(getUserData());

	if (attackTimer >= 1500 && (sqrt(pow(position.getX() - g->player.position.getX(), 2) + pow(position.getY() - g->player.position.getY(), 2))) < 70) {
		playSound(string(MINECRAFT_SOUND_OUH), 0.1f);
		g->player.setHp(g->player.getHp() - 5);
		attackTimer = 0;
	}
}

void Goomba::checkIfSteppedOn() {
	Game* g = reinterpret_cast<Game*>(getUserData());

	if (g->player.getJump() && abs(g->player.position.getX() - position.getX()) < width/2 && (position.getY()) - (g->player.position.getY() + g->player.getHeight()/2) < 4) {
		
		playSound(string(GOOMBAS_JUMP_SOUND),0.1f, false);
		g->player.setJump(true);
		g->gravity = Vect(0, 5);
		g->player.velocity = Vect(0, -40);
		setActiveStatus(false);
		g->score++;
	}
}
