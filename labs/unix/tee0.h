#define _POSIX_C_SOURCE 200809L
// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// read
#include <unistd.h>

#define READ_BYTES 1024
int main(int argc, char* argv[]);
void tee0(char* filepath);
void write0(int fd, char *buffer, int cantidad);
