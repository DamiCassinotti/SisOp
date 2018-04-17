#include "ln1.h"

int main(int argc, char *argv[]) {
	if (argc != 3)
		return -1;
	if (!fileExists(argv[1])){
		printf ("ln: failed to access '%s': No such file or directory\n", argv[1]);
		return -1;
	}
	ln1(argv[1], argv[2]);
	return 0;
}

void ln1(const char* file, const char* new_file) {
	link(file, new_file);
}

int fileExists(const char* file) {
	struct stat buf;
	int result = stat(file, &buf);
	if (result < 0)
		return 0;
	return 1;
}
