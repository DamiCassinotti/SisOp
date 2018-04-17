#include "cp1.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc != 3)
		return -1;
	cp1(argv[1], argv[2]);
	return 0;
}

void cp1(char* origen, char* destino) {
	char *input_mem, *output_mem;
	off_t page_size = sysconf(_SC_PAGE_SIZE);
	int input_fd = open(origen, O_RDONLY);
	int output_fd = open(destino, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	off_t tamano_total = get_file_size(origen);
	ftruncate(output_fd, tamano_total);
	off_t copiado = 0;
	while (copiado < tamano_total) {
		size_t a_copiar;
		if (tamano_total - copiado >= page_size)
			a_copiar = page_size;
		else
			a_copiar = tamano_total - copiado;
		input_mem = mmap(NULL, a_copiar, PROT_READ, MAP_PRIVATE, input_fd, copiado);
		output_mem = mmap(NULL, a_copiar, PROT_READ|PROT_WRITE, MAP_SHARED, output_fd, copiado);
		memcpy(output_mem, input_mem, a_copiar);
		munmap(input_mem, a_copiar);
		munmap(output_mem, a_copiar);
		copiado += a_copiar;
	}
	close(input_fd);
	close(output_fd);
}

off_t get_file_size(char* file) {
	struct stat buf;
	stat(file, &buf);
	return buf.st_size;
}
