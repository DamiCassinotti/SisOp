#include "stat0.h"

int main(int argc, char* argv[]) {
	if (argc != 2)
		return -1;
	stat0(argv[1]);
	return 0;
}

void stat0(const char* file) {
	struct stat buf;
	stat(file, &buf);
	printf("Size: %ld\n", buf.st_size);
	printf("File: %s\n", file);
	char* fileType;
	if (S_ISREG(buf.st_mode))
		fileType = "regular file";
	else
		fileType = "directory";
	printf("Type: %s\n", fileType);
}
