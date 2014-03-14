#ifndef COLOR_H
#define COLOR_H

class Color {

public:

	Color();

	Color(float r, float g, float b);

	float r, g, b;

	void print() const;

	void reset();

	Color operator=(const Color& color);

	Color operator+(const Color& color) const;

	Color operator+=(const Color& color);

	Color operator-(const Color& color) const;

	Color operator*(const Color& color) const;

	Color operator/(const Color& color) const;

	Color operator*(float factor) const;

	Color operator/(float divisor) const;

	bool black();

};

#endif