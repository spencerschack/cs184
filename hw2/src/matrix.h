#ifndef MATRIX_H
#define MATRIX_H

class Matrix {

private:

	float mat[4][4];

public:

	Matrix();

	Vector operator*(const Vector& vector);

};

#endif