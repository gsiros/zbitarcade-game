#include "Player.h"
#include "Projectile.h"
void Player::attack() {
	projectile_list.push_back(new Projectile(40,40,position.getX(), position.getY(),"assets\\Haduken"));
}