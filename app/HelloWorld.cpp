#include <iostream>
#include <graphics.h>
#include <vector>

using namespace graphics;
using namespace std;

bool ok_spacecraft = true;
bool ok = false;
bool ok_rock = false;

struct SpaceInvaders {
	float x_of_SpaceCraft = 350;
	float y_of_SpaceCraft = 250;
	float projectile_speed = 0.5;
	float projectile_x, projectile_y;
	float rock_x, rock_y;
	float rock_speed;
	float rock_size;
};

void drawRock() {

	if (ok_rock) {
		SpaceInvaders* si = (SpaceInvaders*)getUserData();
		Brush br;
		br.fill_opacity = 1;
		br.outline_opacity = 0;
		setOrientation(45);
		br.texture = "assets\\meteorite.png";
		drawRect(si->rock_x, si->rock_y, si->rock_size, si->rock_size, br);
	}
}

void drawProjectile() {
	
	if (ok && ok_spacecraft) {
		SpaceInvaders* dummy = (SpaceInvaders*)getUserData();
		Brush br;
		br.fill_opacity = 1;
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		drawRect(dummy->projectile_x, dummy->projectile_y-50, 5, 10, br);
	}
}

void drawShip(){
	
	if (ok_spacecraft) {
		SpaceInvaders* dummy = (SpaceInvaders*)getUserData();
		Brush br;
		br.fill_opacity = 1;
		br.outline_opacity = 0;
		br.texture = "assets\\spacecraft.png";
		drawRect(dummy->x_of_SpaceCraft, dummy->y_of_SpaceCraft, 100, 100, br);
	}
}

void draw() {
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "assets\\galaxyBG.png";
	drawRect(350,250, 700, 500, br);
	drawShip();
	drawProjectile();
	drawRock();
}

void update(float ms) {

	SpaceInvaders* si = (SpaceInvaders*)getUserData();

	// Handle Projectile x Rock collision:
	if (ok && ok_rock && abs(si->projectile_y - si->rock_y)<70 && abs(si->projectile_x - si->rock_x) < 20) {
		playSound("assets\\boom.mp3", 1);
		ok = false;
		si->rock_x = rand() % 750 + 1;
		si->rock_y = -60;
		si->rock_size = rand() % 50 + 30;
		si->rock_speed = ((rand() % 9 + 1) * 0.1) + 0.5;
		ok_rock = true;
	}

	// Handle Spacecraft x Rock collision:
	if (ok_rock && abs(si->y_of_SpaceCraft - si->rock_y) < 60 && abs(si->x_of_SpaceCraft - si->rock_x) < 60) {
		ok_rock = false;
		ok_spacecraft = false;
		stopMusic();
		playSound("assets\\crash.mp3",1);
	}

	MouseState m;
	getMouseState(m);
	if (ok_spacecraft && m.button_left_pressed) {
		playSound("assets\\shoot.wav", 1.f);
		si->projectile_x = si->x_of_SpaceCraft;
		si->projectile_y = si->y_of_SpaceCraft;
		ok = true;
	}
	else if(m.button_right_pressed) {
		si->rock_x = rand() % 750 + 1;
		si->rock_y = -60;
		si->rock_size = rand() % 50 + 30;
		si->rock_speed = ((rand() % 9 + 1) * 0.1)+0.5;
		ok_rock = true;
	}

	if (ok_rock && si->rock_y < 500) {
		si->rock_y += si->rock_speed;
	}
	else if (si->rock_y > 500) {
		si->rock_x = rand() % 750 + 1;
		si->rock_y = -60;
		si->rock_size = rand() % 50 + 30;
		si->rock_speed = ((rand() % 9 + 1) * 0.1) + 0.5;
		ok_rock = true;
	}


	if (ok && si->projectile_y<500) {
		si->projectile_y -= 7;
	}
	else if (si->projectile_y > 500) {
		ok = false;
	}

	if (getKeyState(SCANCODE_W))
	{
		if (si->y_of_SpaceCraft-50==0) {
		
		}
		else {
			si->y_of_SpaceCraft -= 2;
		}
		
	}

	if (getKeyState(SCANCODE_S))
	{
		if (si->y_of_SpaceCraft +50 == 500) {

		}
		else {
			si->y_of_SpaceCraft += 2;
		}
	}

	if (getKeyState(SCANCODE_A))
	{
		if (si->x_of_SpaceCraft -50 == 0) {
		} else {
			si->x_of_SpaceCraft -= 2;
		}
		
	}

	if (getKeyState(SCANCODE_D))
	{
		if (si->x_of_SpaceCraft + 50 == 700) {
		}
		else {
			si->x_of_SpaceCraft += 2;
		}
	}
}

int main() {
	// testing the sgg lib
	SpaceInvaders* si = new SpaceInvaders();
	
	createWindow(700, 500, "Space Invaders");	
	setUserData(si);
	setDrawFunction(draw);
	setUpdateFunction(update);
	playMusic("assets\\action52.mp3",.8);
	startMessageLoop();
	destroyWindow();
	return 0;
}