#include "options.h"

bool Options::has_next() {
	return index < argc;
}

char* Options::next() {
	if(has_next()) {
		return argv[index++];
	} else {
		printf("Not enough arguments.\n");
		exit(1);
	}
}

Options::Options(int argc, char* argv[]) : argc(argc), argv(argv), index(1) {
	char* option;
	while(has_next()) {
		option = next();
		// Ensure the flag is in the format "-f".
		if(option[0] == '-' && option[1] != 0 && option[2] == 0) {
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
