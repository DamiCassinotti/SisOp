#define _POSIX_C_SOURCE 200809L
// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// read
#include <unistd.h>

#define READ_BYTES 10

int main(int argc, char* argv[]);
void cp0(const char* input, const char* output);
// Return read-only file descriptor
int openForReading(const char *file);
// Return write-only file descriptor
int openOrCreateForWriting(const char *file);
// read READ_BYTES bytes from descriptor and stores in buffer
int read0(int descriptor, char *buffer);
// prints on descriptor cantidad from buffer;
void writeInto(int output_descriptor, char *buffer, int cantidad);
