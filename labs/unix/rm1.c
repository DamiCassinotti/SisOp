#include "rm1.h"

int main(int argc, char *argv[]) {
	if (argc != 2)
		return -1;
	rm1(argv[1]);
	if (errno == EISDIR) {
		char errMsg[strlen(argv[1]) + 20]; // mensaje + directorio
		sprintf(errMsg, "rm: cannot remove '%s'", argv[1]);
		perror(errMsg);
	}
	return 0;
}

void rm1(char* file) {
	unlink(file);
}
