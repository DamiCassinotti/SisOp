#include "mv0.h"

int main(int argc, char *argv[]) {
	if (argc != 3)
		return -1;
	if (!fileExists(argv[1])){
		char errMsg[strlen(argv[1]) + 18]; // mensaje + directorio
		sprintf(errMsg, "mv: cannot stat '%s'", argv[1]);
		perror(errMsg);
		return -1;
	}
	mv0(argv[1], argv[2]);
	return 0;
}

void mv0(const char* oldPath, const char* newPath) {
	rename(oldPath, newPath);
}

int fileExists(const char* file) {
	struct stat buf;
	int result = stat(file, &buf);
	if (result < 0)
		return 0;
	return 1;
}
