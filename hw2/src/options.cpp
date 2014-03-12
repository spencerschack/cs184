using namespace std;

class Options {

private:

	int argc, index;

	char** argv;

public:

	Options(int argc, char* argv[]) : argc(argc), argv(argv), index(1) {
		char* option;
		while(index < argc) {
			option = next();
			if(option[0] == '-') {
				switch(option[1]) {
					case 'f': // Image filename.
						filename = next();
						break;
					case 'w': // Image width.
						width = atoi(next());
						break;
					case 'h': // Image height.
						height = atoi(next());
						break;
					default:
						printf("Unknown flag: %s\n", option);
						exit(1);
				}
			} else {
				printf("Expected flag, got: %s\n", option);
				exit(1);
			}
		}
	}

	char* next() {
		if(++index >= argc) {
			printf("Not enough arguments.\n");
			exit(1);
		}
		return argv[index];
	}

	string filename;

	int width, height;

};