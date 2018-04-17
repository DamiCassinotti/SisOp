#define _POSIX_C_SOURCE 200809L
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]);
void cp1(char* origen, char* destino);
off_t get_file_size(char* fd);
