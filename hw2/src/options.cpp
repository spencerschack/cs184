using namespace std;

class Options {

public:

	static Options parse(int argc, char* argv[]) {
		Options options;
		int i;
		char* option;
		// Start from 1, skip the program name.
		for(i = 1; i < argc; i++) {
			option = argv[i];
			// Specify the filename to write to.
			if(strcmp(option, "-f") == 0) {
				options.filename = consume(i, argc, argv);
			} else {
				printf("Unknown argument: %s\n", option);
				exit(1);
			}
		}
		return options;
	}

	static char* consume(int &index, int &argc, char* argv[]) {
		if(++index >= argc) {
			printf("Not enough arguments.");
			exit(1);
		}
		return argv[index];
	}

	string filename;

};