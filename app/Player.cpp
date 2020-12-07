#include "Player.h"
#include "Projectile.h"



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