#include "Player.h"
#include "Game.h"
#include "Projectile.h"



void Player::init()
{
	jump = false;
}

void Player::draw()
{
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = assetFile;
	drawRect(position.getX(), position.getY(), width, height, br);

	// Draw Player projectiles from attack:
	for (list<Projectile*>::iterator it = projectile_list.begin(); it != projectile_list.end(); ++it) {
		if (*it != nullptr) {
			// Draw each projectile:
			(*it)->draw();
		}
	}
}

void Player::update()
{
	Game* game = reinterpret_cast<Game*> (getUserData());

	// PLAYER UPDATE

	// If 'W' is pressed:
	if (getKeyState(SCANCODE_W)) {
		jump = true;
	}

	if (jump) {
		position = position + velocity * (getDeltaTime()/70.f);
		velocity = velocity + game->gravity * (getDeltaTime()/70.f);
	}

	// If 'S' is pressed:
	if (getKeyState(SCANCODE_S)) {
		if (position.getY() + height / 2 < WINDOW_HEIGHT)
			position.setY(position.getY() + 2);
		else {
			position.setY(WINDOW_HEIGHT - height / 2);
		}
	}

	// If 'A' is pressed:
	if (getKeyState(SCANCODE_A)) {
		if (position.getX() - width / 3 > 0) {
			position.setX(position.getX() - (getDeltaTime()/4.f));
			setAssetFileMoveLeft();
		}
	}

	// If 'D' is pressed:
	if (getKeyState(SCANCODE_D)) {
		if (position.getX() + width / 3 < WINDOW_WIDTH) {
			position.setX(position.getX() + (getDeltaTime()/4.f));
			setAssetFileMoveRight();
		}
	}

	// If "SPACEBAR" is pressed:
	if (getKeyState(SCANCODE_SPACE)) {
		if (projectile_list.empty()) {
			playSound("assets\\sounds\\fireball_sound_effect.mp3", 0.1f, false);
			attack();

		}
		else if (abs(projectile_list.back()->position.getX() - position.getX()) > 50) {
			playSound("assets\\sounds\\fireball_sound_effect.mp3", 0.1f, false);
			attack();
		}
	}

	// Projectiles movement:
	for (list<Projectile*>::iterator it = projectile_list.begin(); it != projectile_list.end(); ++it) {
		if (*it != nullptr) {
			(*it)->update();
			if (!(*it)->getActiveStatus()) {
				// TODO: what happens with garbage collection?
				it = projectile_list.erase(it);
				if (it == projectile_list.end())
					break;
			}
		}
	}

	if (position.getY() + height / 2 >= WINDOW_HEIGHT)
	{
		position.setY(WINDOW_HEIGHT - height / 2);
		jump = false;
		game->gravity = Vect(0, 5);
		game->player.velocity = Vect(0, -40);
	}



}

void Player::attack() {
	if (assetFile == asset_character_right) {
		projectile_list.push_back(new Projectile(40, 40, position.getX(), position.getY(), "assets\\Haduken"));
		projectile_list.back()->setAssetFileMoveRight();
	}
	else{
		projectile_list.push_back(new Projectile(40, 40, position.getX(), position.getY(), "assets\\Haduken"));
		projectile_list.back()->setAssetFileMoveLeft();
	}
}