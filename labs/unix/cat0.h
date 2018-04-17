#define _POSIX_C_SOURCE 200809L
// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// read
#include <unistd.h>

#define READ_BYTES 10

int main(int argc, char* argv[]);
void cat0(const char *file);
// Return read-only file descriptor
int open0(const char *file);
// read READ_BYTES bytes from descriptor and stores in buffer
int read0(int descriptor, char *buffer);
// prints on stdio cantidad from buffer;
void write0(char* buffer, int cantidad);
