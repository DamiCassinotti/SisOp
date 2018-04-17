#include "touch0.h"

int main(int argc, char* argv[]) {
	if (argc != 2)
		return -1;
	touch0(argv[1]);
	return 0;
}

void touch0(const char *file) {
	int fd = open(file, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	close(fd);
}
