#include <iostream>
#include <graphics.h>

using namespace graphics;

void draw() {
	graphics::Brush br;
	br.fill_opacity = 1;
	br.outline_opacity = 0;
	br.texture = "test1.png";
	drawRect(250, 250, 100, 100, br);
}
void update(float ms) {}

int main() {

	createWindow(500, 500, "Hello World!");
	setDrawFunction(draw);
	setUpdateFunction(update);
	startMessageLoop();
	destroyWindow();
	return 0;
}