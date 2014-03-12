#include "options.h"

Options::Options(int argc, char* argv[]) : argc(argc), argv(argv), index(0) {
	char* option;
	while((option = next(true)) != NULL) {
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

char* Options::next(bool skipAssert) {
	if(++index < argc) {
		return argv[index];
	} else if(skipAssert) {
		return NULL;
	} else {
		printf("Not enough arguments.\n");
		exit(1);
	}
}