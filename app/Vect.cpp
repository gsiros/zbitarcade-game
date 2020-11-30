#include "Vect.h"

Vect::Vect() {
	x = 0.f;
	y = 0.f;
}

Vect::Vect(float x, float y): x(x), y(y) {}

float Vect::getX() { return x; }

float Vect::getY() { return y; }

void Vect::setX(float x) { this->x = x; }

void Vect::setY(float y) { this->y = y; }

Vect Vect::operator+(const Vect& v) {
	return Vect(this->x+v.x, this->y+v.y);
}

Vect Vect::operator-(const Vect& v) {
	return Vect(this->x - v.x, this->y - v.y);
}

Vect Vect::operator*(float num) {
	return Vect(num*this->x, num*this->y);
}