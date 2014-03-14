#include "matrix.h"

Matrix::Matrix() { };

Matrix::Matrix(
	float aa, float ab, float ac, float ad,
	float ba, float bb, float bc, float bd,
	float ca, float cb, float cc, float cd,
	float da, float db, float dc, float dd) {

	matrix[0][0] = aa;
	matrix[0][1] = ab;
	matrix[0][2] = ac;
	matrix[0][3] = ad;

	matrix[1][0] = ba;
	matrix[1][1] = bb;
	matrix[1][2] = bc;
	matrix[1][3] = bd;

	matrix[2][0] = ca;
	matrix[2][1] = cb;
	matrix[2][2] = cc;
	matrix[2][3] = cd;

	matrix[3][0] = da;
	matrix[3][1] = db;
	matrix[3][2] = dc;
	matrix[3][3] = dd;
};

Matrix Matrix::Translation(float x, float y, float z) {
	return Matrix(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1);
}

Matrix Matrix::Scale(float x, float y, float z) {
	return Matrix(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}
