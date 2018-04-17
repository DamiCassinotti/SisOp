#include "cp0.h"

int main(int argc, char* argv[]) {
	if (argc != 3)
		return -1;
	cp0(argv[1], argv[2]);
	return 0;
}

void cp0(const char* input, const char* output) {
	int input_descriptor = openForReading(input);
	int output_descriptor = openOrCreateForWriting(output);
	char buffer[READ_BYTES];
	int leidos;
	while ((leidos = read0(input_descriptor, buffer)) > 0) {
		writeInto(output_descriptor, buffer, leidos);
	}
	close(input_descriptor);
	close(output_descriptor);
}

int openForReading(const char *file) {
	return open(file, O_RDONLY);
}

int openOrCreateForWriting(const char *file) {
	return creat(file, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
}

int read0(int descriptor, char *buffer) {
	return read(descriptor, buffer, READ_BYTES);
}

void writeInto(int output_descriptor, char *buffer, int cantidad) {
	int escritos = 0;
	while (escritos < cantidad) {
		escritos += write(output_descriptor, buffer, cantidad);
	}
}
