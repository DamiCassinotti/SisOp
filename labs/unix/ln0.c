#include "ln0.h"

int main(int argc, char *argv[]) {
	if (argc != 3)
		return -1;
	ln0(argv[1], argv[2]);
	return 0;
}

void ln0(const char* file, const char* link) {
	symlink(file, link);
}
