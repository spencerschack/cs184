#ifndef MATRIX_H
#define MATRIX_H

class Matrix {

private:

	float matrix[4][4];

public:

	Matrix();

	Matrix(float m[16]);

	Matrix(
		float aa, float ab, float ac, float ad,
		float ba, float bb, float bc, float bd,
		float ca, float cb, float cc, float cd,
		float da, float db, float dc, float dd);

	static Matrix Translation(float x, float y, float z);

	static Matrix Scale(float x, float y, float z);

	Matrix inverse();

	Matrix operator*(Matrix& matrix);

	Vector operator*(const Vector& vector);

};

#endif