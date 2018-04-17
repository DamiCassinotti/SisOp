#define _POSIX_C_SOURCE 200809L
// Open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// Close
#include <unistd.h>
// utime
#include <sys/types.h>
#include <utime.h>


int main(int argc, char* argv[]);
void touch1(const char *file);
int fileExists(const char* file);
