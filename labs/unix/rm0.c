#include "rm0.h"

int main(int argc, char *argv[]) {
	if (argc != 2)
		return -1;
	rm0(argv[1]);
	return 0;
}

void rm0(char* file) {
	unlink(file);
}
