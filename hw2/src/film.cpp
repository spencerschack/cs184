#include "../lib/lodepng/lodepng.h"
#include "../lib/lodepng/lodepng.cpp"

using namespace std;
using namespace lodepng;

Film::Film(const Options& options) :
	width(options.width), height(options.height), filename(options.filename) {
	film = vector<ColorCount>(height * width);
};

void Film::commit(const Sample& sample, const Color& color) {
	int x = (int) sample.x, y = (int) sample.y;
	ColorCount& color_count = film.at(y * width + x);
	color_count.color += color;
	color_count.count++;
}

int Film::write_image() {
	int length = width * height, i;
	unsigned char image[3 * length];
	ColorCount color_count;
	Color color;
	float count;
	for(i = 0; i < length; i++) {
		color_count = film[i];
		color = color_count.color;
		count = (float) color_count.count;
		image[(3 * i) + 0] = 255 * fmin(1.0, fmax(0.0, color.r / count));
		image[(3 * i) + 1] = 255 * fmin(1.0, fmax(0.0, color.g / count));
		image[(3 * i) + 2] = 255 * fmin(1.0, fmax(0.0, color.b / count));
	}
	return encode(filename, image, width, height, LCT_RGB);
}
