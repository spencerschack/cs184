#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include "point.h"
#include "normal.h"
#include "ray.h"
#include "local_geo.h"

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

	static Matrix Scale(float s);

	static Matrix Scale(float x, float y, float z);

	static Matrix Rotate(float x, float y, float z, float degree);
	
	void print();

	Matrix inverse();

	Matrix transpose();

	Matrix operator*(Matrix& matrix) const;

	Vector operator*(const Vector& vector) const;

	Point operator*(const Point& point) const;

	Normal operator*(const Normal& normal) const;

	Ray operator*(const Ray& ray) const;

	LocalGeo operator*(const LocalGeo& local) const;

};

#endif