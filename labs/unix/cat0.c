#include "cat0.h"

int main(int argc, char* argv[]) {
	if (argc != 2)
		return -1;
	cat0(argv[1]);
	return 0;
}

void cat0(const char *file) {
	int descriptor = open0(file);
	char buffer[READ_BYTES];
	int leidos;
	while ((leidos = read0(descriptor, buffer)) > 0) {
		write0(buffer, leidos);
	}
	close(descriptor);
}

int open0(const char *file) {
	return open(file, O_RDONLY);
}

int read0(int descriptor, char *buffer) {
	return read(descriptor, buffer, READ_BYTES);
}

void write0(char *buffer, int cantidad) {
	int escritos = 0;
	while (escritos < cantidad) {
		escritos += write(STDOUT_FILENO, buffer, cantidad);
	}
}
