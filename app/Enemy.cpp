#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(float width, float height, float center_x, float center_y, float hp, const string & assetFile, Game* const game) : Character(width, height, center_x, center_y, hp, assetFile, game) {}
