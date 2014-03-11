#ifndef NORMAL_H
#define NORMAL_H

#include "vector.h"

class Normal : public Vector {

public:

	Normal(Vector* vector);

private:

	void normalize();

};

#endif