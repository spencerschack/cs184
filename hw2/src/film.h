#ifndef FILM_H
#define FILM_H

#include <vector>

#include "sample.h"
#include "color.h"
#include "options.h"

using namespace std;

class Film {

private:

	vector<Color> film;

public:

	Film(const Options& options);

	string filename;

	int width, height;

	void commit(const Sample& sample, const Color& color);

	int write_image();

};

#endif