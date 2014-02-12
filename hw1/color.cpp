class Color {

public:

	float r, g, b;

	Color(float r, float g, float b) : r(r), g(g), b(b) { }

	Color(Color* color) {
		r = color->r;
		g = color->g;
		b = color->b;
	}

	Color* operator+(Color* color) {
		return *new Color(this) += color;
	}

	Color* operator+=(Color* color) {
		r += color->r;
		g += color->g;
		b += color->b;
		return this;
	}

	Color* operator-(Color* color) {
		return *new Color(this) -= color;
	}

	Color* operator-=(Color* color) {
		r -= color->r;
		g -= color->g;
		b -= color->b;
		return this;
	}

	Color* operator*(float factor) {
		return *new Color(this) *= factor;
	}

	Color* operator*=(float factor) {
		r *= factor;
		g *= factor;
		b *= factor;
		return this;
	}

	Color* operator/(float divisor) {
		return *new Color(this) /= divisor;
	}

	Color* operator/=(float divisor) {
		r /= divisor;
		g /= divisor;
		b /= divisor;
		return this;
	}

};