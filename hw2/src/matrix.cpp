#include <cmath>

#include "matrix.h"

Matrix::Matrix() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			matrix[i][j] = 0;
		}
	}
};

Matrix::Matrix(float m[16]) {
	int i, j, k = 0;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			matrix[i][j] = m[k++];
		}
	}
}

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

Matrix Matrix::Scale(float s) {
	return Matrix::Scale(s, s, s);
}

Matrix Matrix::Scale(float x, float y, float z) {
	return Matrix(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}

Matrix Matrix::Rotate(float x, float y, float z, float degree) {
  float toRet[16];
  float c = cos(degree * M_PI / 180);
  float s = sin(degree * M_PI / 180);
  float t = 1.0 - c;
  float tx2 = t * pow(x, 2.0);
  float ty2 = t * pow(y, 2.0);
  float tz2 = t * pow(z, 2.0);
  float txy = t * x * y;
  float tyz = t * y * z;
  float txz = t * x * z;
  float sx = s * x;
  float sy = s * y;
  float sz = s * z;
  toRet[0] = tx2 + c;
  toRet[1] = txy - sz;
  toRet[2] = txz + sy;
  toRet[3] = 0;
  toRet[4] = txy + sz;
  toRet[5] = ty2 + c;
  toRet[6] = tyz - sx;
  toRet[7] = 0;
  toRet[8] = txz - sy;
  toRet[9] = tyz + sx;
  toRet[10] = tz2 + c;
  toRet[11] = 0;
  toRet[12] = 0;
  toRet[13] = 0;
  toRet[14] = 0;
  toRet[15] = 1;
  return Matrix(toRet);
}

void Matrix::print() const {
  printf("Matrix<{");
  int x, y;
  for(y = 0; y < 4; y++) {
    printf("{");
    for(x = 0; x < 3; x++) {
      printf("%f, ", matrix[y][x]);
    }
    printf("%f}, ", matrix[y][3]);
  }
  printf("}>\n");
}

Matrix Matrix::transpose() {
  float tmp;
  int x, y;
  Matrix transposed;
  for(y = 0; y < 4; y++) {
    for(x = 0; x < 4; x++) {
      transposed.matrix[y][x] = matrix[x][y];
    }
  }
  return transposed;
}

Matrix Matrix::inverse() {
	float invOut[16];
	float m[16];

    float inv[16], det;
    int i, j, k=0;
    for (i = 0; i < 4; i++) {
    	for (j = 0; j < 4; j++) {
    		m[k] = matrix[i][j];
    		k++;
    	}
    }
    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if(det == 0) {
      printf("An attempt was made to invert an invertible matrix.\n");
      exit(1);
    }

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return Matrix(invOut);
}

Matrix Matrix::operator*(Matrix& factor) const {
	Matrix product;
	int i, j, k;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			for(k = 0; k < 4; k++) {
				product.matrix[i][j] += matrix[i][k] * factor.matrix[k][j];
			}
		}
	}
	return product;
}

Vector Matrix::operator*(const Vector& vector) const {
  Vector multiplied;
  multiplied.x = matrix[0][0] * vector.x + matrix[0][1] * vector.y + matrix[0][2] * vector.z;
  multiplied.y = matrix[1][0] * vector.x + matrix[1][1] * vector.y + matrix[1][2] * vector.z;
  multiplied.z = matrix[2][0] * vector.x + matrix[2][1] * vector.y + matrix[2][2] * vector.z;
  return multiplied;
};

Normal Matrix::operator*(const Normal& normal) const {
  Normal multiplied;
  multiplied.x = matrix[0][0] * normal.x + matrix[0][1] * normal.y + matrix[0][2] * normal.z;
  multiplied.y = matrix[1][0] * normal.x + matrix[1][1] * normal.y + matrix[1][2] * normal.z;
  multiplied.z = matrix[2][0] * normal.x + matrix[2][1] * normal.y + matrix[2][2] * normal.z;
  multiplied.normalize();
  return multiplied;
};

Point Matrix::operator*(const Point& point) const {
  Point multiplied;
  multiplied.x = matrix[0][0] * point.x + matrix[0][1] * point.y + matrix[0][2] * point.z + matrix[0][3];
  multiplied.y = matrix[1][0] * point.x + matrix[1][1] * point.y + matrix[1][2] * point.z + matrix[1][3];
  multiplied.z = matrix[2][0] * point.x + matrix[2][1] * point.y + matrix[2][2] * point.z + matrix[2][3];
  return multiplied;
};
