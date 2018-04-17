#include "tee0.h"

int main(int argc, char* argv[]) {
	if (argc != 2)
		return -1;
	tee0(argv[1]);
	return 0;
}

void tee0(char* filepath) {
	int leidos = 0;
	int output_fd = creat(filepath, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	char buffer[READ_BYTES];
	while ((leidos = read(STDIN_FILENO, buffer, READ_BYTES)) > 0) {
		write0(STDOUT_FILENO, buffer, leidos);
		write0(output_fd, buffer, leidos);
	}
	close(output_fd);
}

void write0(int fd, char *buffer, int cantidad) {
	int escritos = 0;
	while (escritos < cantidad) {
		escritos += write(fd, buffer, cantidad);
	}
}
