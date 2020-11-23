#include <iostream>
#include <graphics.h>

using namespace graphics;

void draw() {}
void update(float ms) {}

int main() {

	createWindow(500, 500, "Hello World!");
	setDrawFunction(draw);
	setUpdateFunction(update);
	startMessageLoop();
	return 0;
	// Deleted test class.
	// new comment
}