#include "Metrics.h"

#include "Player.h"
#include "Game.h"
#include "Projectile.h"

Player::~Player() {
	while (!projectile_list.empty()) {
		delete projectile_list.front();
		projectile_list.pop_front();
	}
}

void Player::init()
{
	jump = false;
	attackTimer = 0;
	active = true;
	attackSpeed = float(DEFAULT_ATTACK_SPEED);
	movementSpeed = float(DEFAULT_MOVEMENT_SPEED);
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

	// PLAYER UPDATE
	if (attackTimer < 500) {
		attackTimer += getDeltaTime();
	}
	else {
		attackTimer = 500;
	}

	if (hp <= 0) {
		active = false;
		game->arrow_offset = 0.f;
		game->retry_choice = AGAIN;
		game->state = RETRY;
		stopMusic();
		playMusic(string(MARIO_KART_LOSING_SOUND_EFFECT), 0.1f);
	}

	// If 'W' is pressed:
	if (getKeyState(SCANCODE_W)) {
		jump = true;
	}

	if (jump) {
		position = position + velocity * (getDeltaTime()/70.f);
		velocity = velocity + game->gravity * (getDeltaTime()/70.f);
	}

	// If 'A' is pressed:
	if (getKeyState(SCANCODE_A)) {
		if (position.getX() - width / 3 > 0) {
			position.setX(position.getX() - (getDeltaTime()/movementSpeed));
			setAssetFileMoveLeft();
		}
	}

	// If 'D' is pressed:
	if (getKeyState(SCANCODE_D)) {
		if (position.getX() + width / 3 < CANVAS_WIDTH) {
			position.setX(position.getX() + (getDeltaTime()/movementSpeed));
			setAssetFileMoveRight();
		}
	}

	// If "SPACEBAR" is pressed:
	if (getKeyState(SCANCODE_SPACE)) {
		if (attackTimer >= attackSpeed) {
			playSound("assets\\sounds\\fireball_sound_effect.mp3", 0.1f, false);
			attack();
			attackTimer = 0;
		}
	}

	// Projectiles movement:
	for (list<Projectile*>::iterator it = projectile_list.begin(); it != projectile_list.end(); ++it) {
		if (*it != nullptr) {
			(*it)->update();
			if (!(*it)->getActiveStatus()) {
				delete* it;
				it = projectile_list.erase(it);
				if (it == projectile_list.end())
					break;
			}
		}
	}

	if (upgraded) {
		duration -= getDeltaTime();
	}

	if (upgraded && duration <= 0) {
		upgraded = false;
		setMovementSpeed(float(DEFAULT_MOVEMENT_SPEED));
		setAttackSpeed(float(DEFAULT_ATTACK_SPEED));
		if (this->assetFile == this->asset_character_left) {
			this->asset_character_left = string(GOKU_NEW) + "_left.png";
			this->asset_character_right = string(GOKU_NEW) + "_right.png";
			this->assetFile = asset_character_left;
		}
		else {
			this->asset_character_left = string(GOKU_NEW) + "_left.png";
			this->asset_character_right = string(GOKU_NEW) + "_right.png";
			this->assetFile = asset_character_right;
		}
		this->width -= 15;
	}

	if (position.getY() + height / 2 >= CANVAS_HEIGHT)
	{
		position.setY(CANVAS_HEIGHT - height / 2);
		jump = false;
		game->gravity = Vect(0, 5);
		game->player->velocity = Vect(0, -40);
	}

}

void Player::attack() {
	if (assetFile == asset_character_right) {
		projectile_list.push_back(new Projectile(40, 40, position.getX(), position.getY(), "assets\\Haduken", game));
		projectile_list.back()->setAssetFileMoveRight();
	}
	else{
		projectile_list.push_back(new Projectile(40, 40, position.getX(), position.getY(), "assets\\Haduken", game));
		projectile_list.back()->setAssetFileMoveLeft();
	}
}

void Player::setJump(bool status) {
	this->jump = status;
}

bool Player::getJump() {
	return this->jump;
}

void Player::upgrade(float duration, float attackSpeed, float movementSpeed, string assetFile) {
	this->duration = duration;
	this->setAttackSpeed(attackSpeed);
	this->setMovementSpeed(movementSpeed);
	this->setUpgraded(true);
	if (this->assetFile == this->asset_character_left) {
		this->asset_character_left = assetFile + "_left.png";
		this->asset_character_right = assetFile + "_right.png";
		this->assetFile = asset_character_left;
	}
	else {
		this->asset_character_left = assetFile + "_left.png";
		this->asset_character_right = assetFile + "_right.png";
		this->assetFile = asset_character_right;
	}
	this->width += 15;
	playSound(string(SUPER_MARIO_STAR_MUSIC), 0.25f);
}