#include <iostream>
#include <graphics.h>

using namespace graphics;

struct Game {

};

void draw() {
	Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "assets\\fish.png";
	drawRect(250, 250, 500, 500, br);
}
void update(float ms) {}

int main() {
	Game* g = new Game();
	createWindow(500, 500, "Hello World!");
	setUserData(&g);
	setDrawFunction(draw);
	setUpdateFunction(update);
	startMessageLoop();
	destroyWindow();
	return 0;
}