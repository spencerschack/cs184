#ifndef COLOR_H
#define COLOR_H

class Color {

public:

	Color();

	Color(float r, float g, float b);

	float r, g, b;

	Color operator+(Color color);

	Color operator-(Color color);

	Color operator*(Color color);

	Color operator/(Color color);

	Color operator*(float factor);

	Color operator/(float divisor);

};

#endif