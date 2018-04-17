#include "touch1.h"

int main(int argc, char* argv[]) {
	if (argc != 2)
		return -1;
	touch1(argv[1]);
	return 0;
}

void touch1(const char *file) {
	if (!fileExists(file)) {
		int fd = open(file, O_CREAT|O_RDWR, \
			S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
		close(fd);
	} else {
		utime(file, NULL);
	}
}

int fileExists(const char* file) {
	struct stat buf;
	int result = stat(file, &buf);
	if (result < 0)
		return 0;
	return 1;
}
