#include "color.h"

Color::Color() : r(0), g(0), b(0) { };

Color::Color(float r, float g, float b) : r(r), g(g), b(b) { };

void Color::print() {
	printf("Color<r: %f, g: %f, b: %f>\n", r, g, b);
}

void Color::reset() {
	r = 0;
	b = 0;
	g = 0;
}

Color Color::operator=(const Color& color) {
	r = color.r;
	g = color.g;
	b = color.b;
	return *this;
};

Color Color::operator+(const Color& color) {
	return Color(r + color.r, g + color.g, b + color.b);
};

Color Color::operator-(const Color& color) {
	return Color(r - color.r, g - color.g, b - color.b);
};

Color Color::operator*(const Color& color) {
	return Color(r * color.r, g * color.g, b * color.b);
};

Color Color::operator/(const Color& color) {
	return Color(r / color.r, g / color.g, b / color.b);
};

Color Color::operator*(float factor) {
	return Color(r * factor, g * factor, b * factor);
};

Color Color::operator/(float divisor) {
	return Color(r / divisor, g / divisor, b / divisor);
};