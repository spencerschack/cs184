#ifndef FILM_H
#define FILM_H

#include <vector>
#include <utility>

#include "sample.h"
#include "color.h"
#include "options.h"

using namespace std;

struct ColorCount {
	Color color;
	int count = 0;
};

class Film {

private:

	vector<ColorCount> film;

public:

	Film(const Options& options);

	string filename;

	int width, height;

	void commit(const Sample& sample, const Color& color);

	int write_image();

};

#endif