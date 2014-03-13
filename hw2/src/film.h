#ifndef FILM_H
#define FILM_H

#include <vector>

#include "sample.h"
#include "color.h"

using namespace std;

class Film {

private:

	vector<Color> film;

public:

	Film(int width, int height);

	int width, height;

	void commit(const Sample& sample, const Color& color);

	int write_to_file(string filename);

};

#endif