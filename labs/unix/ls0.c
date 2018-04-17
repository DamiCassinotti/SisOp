#include "ls0.h"

int main() {
	ls0();
	return 0;
}

void ls0() {
	DIR* directory = opendir(".");
	struct dirent* entry;
	while ((entry = readdir(directory)) != NULL) {
		printf("%s\n", entry->d_name);
	}
	closedir(directory);
}
