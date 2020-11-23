#include <iostream>
#include <graphics.h>
#include <vector>

using namespace graphics;
using namespace std;

bool ok = false;

struct SpaceInvaders {
	float x_of_SpaceCraft = 350;
	float y_of_SpaceCraft = 250;
	float projectile_speed = 0.5;
	float projectile_x, projectile_y;
};

void drawProjectile() {
	
	if (ok) {
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
	SpaceInvaders* dummy = (SpaceInvaders*)getUserData();
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "assets\\spacecraft.png";
	drawRect(dummy->x_of_SpaceCraft,dummy->y_of_SpaceCraft,100,100,br);
}

void draw() {
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "assets\\galaxyBG.png";
	drawRect(350,250, 700, 500, br);
	drawShip();
	drawProjectile();
}

void update(float ms) {

	SpaceInvaders* si = (SpaceInvaders*)getUserData();

	MouseState m;
	getMouseState(m);
	if (m.button_left_pressed) {
		playSound("assets\\shoot.wav", 1.f);
		si->projectile_x = si->x_of_SpaceCraft;
		si->projectile_y = si->y_of_SpaceCraft;
		ok = true;
	}
	if (ok && si->projectile_y<500) {
		si->projectile_y -= 7;
	}
	else if (si->projectile_y > 500) {
		ok = false;
	}

	if (getKeyState(SCANCODE_W))
	{
		si->y_of_SpaceCraft -= 2;
	}

	if (getKeyState(SCANCODE_S))
	{
		si->y_of_SpaceCraft += 2;
	}

	if (getKeyState(SCANCODE_A))
	{
		si->x_of_SpaceCraft -= 2;
	}

	if (getKeyState(SCANCODE_D))
	{
		si->x_of_SpaceCraft += 2;
	}
}

int main() {
	// testing the sgg lib
	SpaceInvaders* si = new SpaceInvaders();
	
	createWindow(700, 500, "Hello World!");	
	setUserData(si);
	setDrawFunction(draw);
	setUpdateFunction(update);
	playMusic("assets\\action52.mp3",1.);
	startMessageLoop();
	destroyWindow();
	return 0;
}